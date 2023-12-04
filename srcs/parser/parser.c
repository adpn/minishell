/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:46:55 by alexphil          #+#    #+#             */
/*   Updated: 2023/12/04 11:40:13 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	syntax_check(t_tools *tools)
{
	t_lex	*lex;

	lex = tools->lex_list;
	if (lex->operator == PIPE)
		return (parser_token_error(tools, lex->operator));
	while (lex)
	{
		if (lex->operator != WORD)
			if ((lex->prev && lex->prev->operator != WORD)
				|| (lex->next && lex->next->operator != WORD)
				|| lex->next == NULL)
				return (parser_token_error(tools, lex->operator));
		lex = lex->next;
	}
	return (EXIT_SUCCESS);
}

void	parser(t_tools *tools)
{
	t_lex	*head;

	head = tools->lex_list;
	if (syntax_check(tools))
	{
		tools->error_code = 2;
		resetools(tools);
		return ;
	}
	tools->pipes = count_pipes(tools->lex_list);
	tools->cmds = NULL;
	while (tools->lex_list)
		new_cmd(tools);
	tools->lex_list = head;
}
