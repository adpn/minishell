/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:12:58 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/23 10:57:37 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	seek_cmd(t_tools *tools, t_cmds *cmd)
{
	extern char	**environ;
	char		*cmd_name;
	char		*cmd_path;
	int			i;

	if (!access(cmd->args[0], F_OK))
		execve(cmd->args[0], cmd->args, environ);
	i = -1;
	cmd_name = ft_strjoin("/", cmd->args[0]);
	while (tools->paths[++i])
	{
		cmd_path = ft_strjoin(tools->paths[i], cmd_name);
		if (!access(cmd_path, F_OK))
			execve(cmd_path, cmd->args, environ);
		free(cmd_path);
	}
	free(cmd_name);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
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
		exit_code = seek_cmd(tools, cmd);
	return (exit_code);
}

void	dup_cmd(t_tools *tools, t_cmds *cmd, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		error_mgmt(tools, 1);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		error_mgmt(tools, 1);
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
	seek_heredoc(tools, cmd);
	pid = fork();
	if (pid < 0)
		error_mgmt(tools, 2);
	if (pid == 0)
		handle_cmd(tools, cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		tools->error_code = WEXITSTATUS(status);
}
