/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:46:55 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/23 17:09:40 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_check(t_tools *tools)
{
	t_lex	*lex;

	lex = tools->lex_list;
	if (lex->operator != WORD)
		return ; // error_mgmt
	while (lex)
	{
		if (lex->operator != WORD)
			if (lex->prev && lex->prev->operator != WORD
				|| lex->next && lex->next->operator != WORD
				|| lex->next == NULL)
				return ; // error_mgmt
		lex = lex->next;
	}
}

void	init_cmd(t_cmds *cmd)
{
	cmd->args = NULL;
	cmd->builtin = NULL;
	cmd->nb_redirects = 0;
	cmd->redirects = NULL;
	cmd->next = NULL;
}

void	add_redirect()
{
	;
}

void	new_redirect()
{
	;
}

void	*get_redirects(t_tools *tools, t_cmds *cmd)
{
	if (tools->lex_list->operator == HEREDOC)
		tools->heredoc = true;
	else if (tools->lex_list->operator == R_INPUT)
	{
		// create new redirections node with operator INPUT and word = next word node;
	}
	else if (tools->lex_list->operator == R_OUTPUT)
	{
		;
	}
	else if (tools->lex_list->operator == R_APP)
	{
		;
	}
	add_redirect();
}

void	add_cmd(t_tools *tools, t_cmds *cmd)
{
	t_cmds	*tmp;

	if (!tools->cmds)
		tools->cmds = cmd;
	else
	{
		tmp = tools->cmds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
	cmd->next = NULL;
}

void	new_cmd(t_tools *tools)
{
	t_cmds	*cmd;
	int		nb_args;
	int		i;

	cmd = malloc(sizeof(t_cmds));
	if (!cmd)
		; // error_mgmt
	init_cmd(cmd);
	nb_args = count_args(tools->lex_list);
	cmd->args = malloc(sizeof(char *) * nb_args);
	i = 0;
	while (tools->lex_list->operator == WORD)
	{
		cmd->args[i++] = ft_strdup(tools->lex_list->word);
		tools->lex_list = tools->lex_list->next;
	}
	while (tools->lex_list && tools->lex_list->operator != PIPE)
		get_redirects(tools, cmd);
	add_cmd(tools, cmd);
}

void	parser(t_tools *tools)
{
	syntax_check(tools);
	tools->pipes = count_pipes(tools->lex_list);
	while (tools->lex_list)
		new_cmd(tools);
}
