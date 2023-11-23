/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:49:41 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/22 14:26:49 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_cmds(t_cmds *cmd)
{
	t_cmds	*next;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->args)
			ft_free_split(cmd->args);
		if (cmd->redirects)
			; // use adupin free lex function
		if (cmd->hd_filename)
			free(cmd->hd_filename);
		free(cmd);
		cmd = next;
	}
}

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
	; // init signals ?
}

void	resetools(t_tools *tools)
{
	free_cmds(tools->cmds);
	// free lexer ?
	if (tools->pid)
		free(tools->pid);
	if (tools->paths)
		ft_free_split(tools->paths);
	initools(tools);
	tools->reset = TRUE;
	// return to readline/ms loop for next input once cleanup is done
}
