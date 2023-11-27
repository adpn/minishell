/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:37:38 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/27 11:58:13 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_append(t_lex *redirect)
{
	int	fd;

	if (redirect->operator == R_APP)
		fd = open(redirect->word, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirect->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

int	check_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ",
			STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	check_outfile(t_lex *redirect)
{
	int	fd;

	fd = check_append(redirect);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ",
			STDERR_FILENO);
		ft_putstr_fd(redirect->word, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	check_redirects(t_cmds *cmd)
{
	t_lex	*redirect;

	redirect = cmd->redirects;
	while (redirect)
	{
		if (redirect->operator == R_INPUT)
		{
			if (check_infile(redirect->word))
				return (EXIT_FAILURE);
		}
		else if (redirect->operator == HEREDOC)
		{
			if (check_infile(cmd->hd_filename))
				return (EXIT_FAILURE);
		}
		else if (redirect->operator == R_OUTPUT || redirect->operator == R_APP)
		{
			if (check_outfile(redirect))
				return (EXIT_FAILURE);
		}
		redirect = redirect->next;
	}
	return (EXIT_SUCCESS);
}
