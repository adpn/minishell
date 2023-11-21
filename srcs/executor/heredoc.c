/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:24:45 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/21 09:27:52 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	heredoc(t_tools *tools, t_lex *heredoc, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(">");
	while (line && ft_strncmp(heredoc->word, line, ft_strlen(heredoc->word))
		&& !tools->stop_heredoc)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(">");
	}
	free(line);
	if (tools->stop_heredoc || !line)
		return (EXIT_FAILURE);
	if (fd)
		close(fd);
	return (EXIT_SUCCESS);
}

int	init_heredoc(t_tools *tools, t_lex *heredoc, char *temp_file)
{
	int	sl;

	sl = EXIT_SUCCESS;
	tools->stop_heredoc = 0;
	tools->in_heredoc = 1;
	sl = create_hd_file(tools, heredoc, temp_file);
	tools->in_heredoc = 0;
	tools->heredoc = true;
	return (sl);
}

char	*name_hd_file(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("/build/.tmp_hd_file_", num);
	free(num);
	return (file_name);
}

void	get_heredoc(t_tools *tools, t_cmds *cmd)
{
	t_lex	*start;
	int		sl;

	start = cmd->redirects;
	while (cmd->redirects)
	{
		if (cmd->redirects->operator == HEREDOC)
		{
			if (cmd->hd_filename)
				free(cmd->hd_filename);
			cmd->hd_filename = gen_hd_filename();
			sl = heredoc(tools, cmd->redirects, cmd->hd_filename);
			if (sl)
			{
				tools->error_code = 1;
				return (resetools(tools));
			}
		}
		cmd->redirects = cmd->redirects->next;
	}
	cmd->redirects = start;
	return (EXIT_SUCCESS);
}
