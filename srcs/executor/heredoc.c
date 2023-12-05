/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:24:45 by alexphil          #+#    #+#             */
/*   Updated: 2023/12/05 14:36:19 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	ft_heredoc(t_tools *tools, t_lex *heredoc, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(">");
	while (line && ft_strncmp(heredoc->word, line, ft_strlen(line)
			+ ft_strlen(heredoc->word)) && !tools->stop_heredoc)
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
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	tools->stop_heredoc = 0;
	tools->in_heredoc = 1;
	exit_code = ft_heredoc(tools, heredoc, temp_file);
	tools->in_heredoc = 0;
	tools->heredoc = true;
	return (exit_code);
}

char	*name_hd_file(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("build/.tmp_hd_file_", num);
	free(num);
	return (file_name);
}

int	seek_heredoc(t_tools *tools, t_cmds *cmd)
{
	t_lex	*start;
	int		exit_code;

	start = cmd->redirects;
	cmd->hd_filename = NULL;
	while (cmd->redirects)
	{
		if (cmd->redirects->operator == HEREDOC)
		{
			if (cmd->hd_filename)
				free(cmd->hd_filename);
			cmd->hd_filename = name_hd_file();
			exit_code = init_heredoc(tools, cmd->redirects, cmd->hd_filename);
			if (exit_code)
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
