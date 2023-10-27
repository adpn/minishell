/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:59:54 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/26 14:11:04 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "struct.h"

void	add_redirect(t_cmds *cmd, t_lex *redirect)
{
	t_lex	*tmp;

	if (!cmd->redirects)
	{
		cmd->redirects = redirect;
		redirect->prev = NULL;
	}
	else
	{
		tmp = cmd->redirects;
		while (tmp->next)
			tmp = tmp->next;
		redirect->prev = tmp;
		tmp->next = redirect;
	}
	redirect->next = NULL;
}

void	new_redirect(t_tools *tools, t_cmds *cmd)
{
	t_lex	*node;

	node = ft_xmalloc(sizeof(t_lex));
	node->operator = tools->lex_list->operator;
	tools->lex_list = tools->lex_list->next;
	node->word = ft_xstrdup(tools->lex_list->word);
	tools->lex_list = tools->lex_list->next;
	while (tools->lex_list && tools->lex_list->operator == WORD)
		tools->lex_list = tools->lex_list->next;
	add_redirect(cmd, node);
}

void	get_redirects(t_tools *tools, t_cmds *cmd)
{
	if (tools->lex_list->operator == HEREDOC)
		tools->heredoc = true;
	else
		new_redirect(tools, cmd);
}
