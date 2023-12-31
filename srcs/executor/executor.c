/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:08:46 by alexphil          #+#    #+#             */
/*   Updated: 2023/12/04 13:32:16 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	expand_cmd(t_tools *tools, t_cmds *cmd)
{
	t_lex	*start;

	start = cmd->redirects;
	expand(cmd->args, tools);
	while (cmd->redirects)
	{
		if (cmd->redirects->word)
			cmd->redirects->word = complete_clean(cmd->redirects->word, tools);
		cmd->redirects = cmd->redirects->next;
	}
	cmd->redirects = start;
}

int	multi_fork(t_tools *tools, int end[2], int fd_in, t_cmds *cmd)
{
	static int	i = 0;

	if (tools->reset == TRUE)
	{
		i = 0;
		tools->reset = FALSE;
	}
	tools->pid[i] = fork();
	if (tools->pid[i] < 0)
		error_mgmt(tools, 2);
	if (tools->pid[i] == 0)
		dup_cmd(tools, cmd, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

int	check_heredoc_fd(t_tools *tools, int end[2], t_cmds *cmd)
{
	int	fd_in;

	if (tools->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->hd_filename, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

int	wait_pipe(t_tools *tools, int *pid, int pipes)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipes)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		tools->error_code = WEXITSTATUS(status);
	if (tools->sig_called)
		tools->error_code = tools->sig_called;
	return (EXIT_SUCCESS);
}

void	executor(t_tools *tools)
{
	int		fd_in;
	int		end[2];
	t_cmds	*cmds;

	cmds = tools->cmds;
	fd_in = STDIN_FILENO;
	while (cmds)
	{
		expand_cmd(tools, cmds);
		if (cmds->next)
			pipe(end);
		seek_heredoc(tools, cmds);
		multi_fork(tools, end, fd_in, cmds);
		close(end[1]);
		if (cmds->prev)
			close(fd_in);
		fd_in = check_heredoc_fd(tools, end, cmds);
		cmds = cmds->next;
	}
	wait_pipe(tools, tools->pid, tools->pipes);
}
