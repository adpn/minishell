/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:49:41 by alexphil          #+#    #+#             */
/*   Updated: 2023/12/04 13:32:47 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "errors.h"

t_cmds	*rewind_cmds(t_cmds *cmd)
{
	while (cmd && cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}

t_lex	*rewind_lex(t_lex *cmd)
{
	while (cmd && cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}

void	free_cmds(t_cmds *cmd)
{
	t_cmds	*next;

	cmd = rewind_cmds(cmd);
	while (cmd)
	{
		next = cmd->next;
		cmd->redirects = rewind_lex(cmd->redirects);
		if (cmd->args)
			ft_free_split(cmd->args);
		if (cmd->redirects)
			free_lex_chained(cmd->redirects);
		if (cmd->hd_filename)
			free(cmd->hd_filename);
		free(cmd);
		cmd = next;
	}
}

// init signals too ?
void	initools(t_tools *tools)
{
	tools->cmds = NULL;
	tools->lex_list = NULL;
	tools->reset = FALSE;
	tools->pid = NULL;
	tools->heredoc = FALSE;
	tools->stop_heredoc = 0;
	tools->in_heredoc = 0;
	tools->in_cmd = 0;
	tools->paths = ft_split(value_var_environ("PATH"), ':');
	if (!tools->paths)
		error_mgmt(tools, 0);
	init_signals();
}

int	resetools(t_tools *tools)
{
	if (tools->cmds)
		free_cmds(tools->cmds);
	if (tools->pid)
		free(tools->pid);
	if (tools->paths)
		ft_free_split(tools->paths);
	free_lex_chained(get_element(tools->lex_list, 0));
	initools(tools);
	tools->reset = TRUE;
	return (EXIT_SUCCESS);
}
