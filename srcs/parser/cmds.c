/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:59:34 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/25 10:33:14 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "struct.h"

void	init_cmd(t_cmds *cmd)
{
	cmd->args = NULL;
	cmd->builtin = NULL;
	cmd->nb_redirects = 0;
	cmd->redirects = NULL;
}

void	add_cmd(t_tools *tools, t_cmds *cmd)
{
	t_cmds	*tmp;

	if (!tools->cmds)
	{
		tools->cmds = cmd;
		cmd->prev = NULL;
	}
	else
	{
		tmp = tools->cmds;
		while (tmp->next)
			tmp = tmp->next;
		cmd->prev = tmp;
		tmp->next = cmd;
	}
	cmd->next = NULL;
}

void	new_cmd(t_tools *tools)
{
	t_cmds	*cmd;
	int		nb_args;
	int		i;

	if (!tools->lex_list)
		return ;
	cmd = malloc(sizeof(t_cmds));
	if (!cmd)
		; // error_mgmt
	init_cmd(cmd);
	nb_args = count_args(tools->lex_list);
	// printf("nb args: %i\n", nb_args);
	cmd->args = malloc(sizeof(char *) * nb_args);
	if (!cmd->args)
		;
	cmd->nb_redirects = count_redirects(tools->lex_list);
	i = 0;
	while (tools->lex_list && tools->lex_list->operator == WORD)
	{
		cmd->args[i++] = ft_strdup(tools->lex_list->word);
		if (!cmd->args[i - 1])
			;
		tools->lex_list = tools->lex_list->next;
	}
	cmd->args[i] = NULL;
	while (tools->lex_list && tools->lex_list->operator != PIPE)
		get_redirects(tools, cmd);
	add_cmd(tools, cmd);
}
