/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:46:55 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/27 14:36:38 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	syntax_check(t_tools *tools)
{
	t_lex	*lex;

	lex = tools->lex_list;
	if (lex->operator == PIPE)
		exit(1) ; // error_mgmt()
	while (lex)
	{
		if (lex->operator != WORD)
			if ((lex->prev && lex->prev->operator != WORD)
				|| (lex->next && lex->next->operator != WORD)
				|| lex->next == NULL)
				exit(1) ; // error_mgmt()
		lex = lex->next;
	}
}

void	parser(t_tools *tools)
{
	t_lex	*head;

	head = tools->lex_list;
	syntax_check(tools);
	tools->pipes = count_pipes(tools->lex_list);
	tools->cmds = NULL;
	while (tools->lex_list)
		new_cmd(tools);
	parser_display(tools);
	tools->lex_list = head;
}

// Connect ms_echo to main and parser for testing it