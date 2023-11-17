/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:12:58 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/17 10:24:00 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// Does tools->paths get initialized somewhere already ? Do they end with '/' ?
// Not yet.
// tools->paths = ft_split([RETRIEVE PATHS FROM ENVP]) in main when init' tools.
int	find_cmd(t_tools *tools, t_cmds *cmd)
{
	char	*cmdpath;
	int		i;

	if (!access(cmd->args[0], F_OK))
		execve(cmd->args[0], cmd->args, tools->envp);
	i = -1;
	while (tools->paths[++i])
	{
		cmdpath = ft_strjoin(tools->paths[i], cmd->args[0]);
		if (!access(cmdpath, F_OK))
			execve(cmdpath, cmd->args, tools->envp);
		free(cmdpath);
	}
}

void	handle_cmd(t_tools *tools, t_cmds *cmd)
{
	int	exit_code;

	if (cmd->redirects)
		if (check_redirects(cmd->redirects))
			exit(1);
	if (cmd->builtin)
		exit(cmd->builtin(tools, cmd));
	else if (cmd->args[0][0] != '\0')
		exit_code = find_cmd(tools, cmd);
	return (exit_code);
}

void	dup_cmd(t_tools *tools, t_cmds *cmd, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		; // error_mgmt
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		; // error_mgmt
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(tools, cmd);
}

// Add expand to each redirects->word too ?
void	single_cmd(t_tools *tools, t_cmds *cmd)
{
	int	pid;
	int	status;

	expand_cmd(cmd);
	if (cmd->builtin)
		tools->error_code = cmd->builtin(tools, cmd);
	get_heredoc(tools, cmd);
	pid = fork();
	if (pid < 0)
		; // error_mgmt
	if (pid == 0)
		handle_cmd(tools, cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		tools->error_code = WEXITSTATUS(status);
}
