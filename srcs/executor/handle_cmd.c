/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:12:58 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/21 12:16:36 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	find_cmd(t_tools *tools, t_cmds *cmd)
{
	char	*cmd_name;
	char	*cmd_path;
	int		i;

	if (!access(cmd->args[0], F_OK))
		execve(cmd->args[0], cmd->args, tools->envp);
	i = -1;
	cmd_name = ft_strjoin("/", cmd->args[0]);
	while (tools->paths[++i])
	{
		cmd_path = ft_strjoin(tools->paths[i], cmd_name);
		if (!access(cmd_path, F_OK))
			execve(cmd_path, cmd->args, tools->envp);
		free(cmd_path);
	}
	free(cmd_name);
	return (cmd_not_found(cmd->args[0]));
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
