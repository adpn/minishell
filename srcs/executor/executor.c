/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:08:46 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/10 11:47:31 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*cmd_lookup(char *cmd)
{
	char	**tokens;
	char	*cmd_path;
	int		i;

	tokens = ft_split(value_var_environ("PATH"), ':');
	if (!tokens)
		exit_mgmt("Error: split failed\n", EXIT_FAILURE);
	cmd = ft_strjoin("/", cmd);
	if (cmd == NULL)
		exit_mgmt("Error: strjoin failed\n", EXIT_FAILURE);
	i = -1;
	while (tokens[++i])
	{
		cmd_path = ft_strjoin(tokens[i], cmd);
		if (cmd_path == NULL)
			exit_mgmt("Error: strjoin failed\n", EXIT_FAILURE);
		if (access(cmd_path, F_OK) == TRUE)
			return (ft_free_split(tokens), free(cmd), cmd_path);
		free(cmd_path);
	}
	return (ft_free_split(tokens), free(cmd), NULL);
}

void	expend_cmd(t_cmds *cmd)
{
	t_lex	*start;

	expand(cmd->args);
	while (cmd->redirects)
	{
		if (cmd->redirects->word)
			expend(cmd->redirects->word);
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
		return ; // ERROR MGMT
	if (tools->pid[i] == 0)
		dup_cmd(tools, end, fd_in, cmd);
	i++;
	return (EXIT_SUCCESS);
}

int	check_heredoc_fd(t_tools *tools, int end[2], t_cmds *cmd)
{
	int	fd_in;

	if (tools->heredoc)
	{
		close(end[0]);
		open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

// Is that function receiving the correct amount of pipes from count_pipes ?
wait_pipe(t_tools *tools, int *pid, int pipes)
{
	int	i;
	int status;

	i = 0;
	while (i < pipes)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		tools->error_code = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

void	executor(t_tools *tools)
{
	int	end[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (tools->cmds)
	{
		expend_cmd(&tools->cmds);
		if (tools->cmds->next)
			pipe(end);
		get_heredoc(tools, tools->cmds);
		multi_fork(tools, end, fd_in, tools->cmds);
		close(end[1]);
		if (tools->cmds->prev)
			close(fd_in);
		fd_in = check_heredoc_fd(tools, end, tools->cmds);
		// if (tools->cmds->next)
		// 	tools->cmds = tools->cmds->next;
		// else
		// 	break ;
		tools->cmds = tools->cmds->next;
	}
	wait_pipe(tools, tools->pid, tools->pipes);
	// MONDAY TO-DO: Simplecmdfirst ? What for ?
	return (0);
}
