/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:50:34 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/11 15:30:10 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser_tools	init_parser_tools(t_lex *lex_list, t_tools *tools)
{
	t_parser_tools	parser_tools;

	parser_tools.lexer_list = lex_list;
	parser_tools.redirections = NULL;
	parser_tools.num_redirections = 0;
	parser_tools.tools = tools;
	return (parser_tools);
}

void	count_pipes(t_lex *node, t_tools *tools)
{
	tools->pipes = 0;
	while (node)
	{
		if (node->operator == PIPE)
			tools->pipes++;
		node = node->next;
	}
}

int	count_args(t_lex *node)
{
	int	i;

	i = 0;
	while (node && node->operator != PIPE)
	{
		if (node->operator == WORD)
			i++;
		node = node->next;
	}
	return (i);
}

t_lex	*get_next_cmd(t_lex *node)
{
	while (node && node->operator != PIPE)
		node = node->next;
	return (node);
}
