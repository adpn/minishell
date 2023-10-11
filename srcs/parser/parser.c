/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:46:55 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/11 10:24:25 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

t_parser_tools	init_parser_tools(t_lex *lex_list, t_tools *tools)
{
	t_parser_tools	parser_tools;

	parser_tools.lexer_list = lex_list;
	parser_tools.redirections = NULL;
	parser_tools.num_redirections = 0;
	parser_tools.tools = tools;
	return (parser_tools);
}

t_simple_cmds	*init_cmd(t_parser_tools *parser_tools)
{
	
}

int	parser(t_tools *tools)
{
	t_simple_cmds	*cmd;
	t_parser_tools	parser_tools;

	count_pipes(tools->lexer_list, tools);
	while (tools->lexer_list)
	{
		if (tools->lexer_list && tools->lexer_list->operator == PIPE)
			; // delete current node from lexer list (being a pipe)
		parser_tools = init_parser_tools(tools->lexer_list, tools);
		cmd = init_cmd(&parser_tools); // WIP
		if (!cmd)
			; // unified error_mgmt
		if (!tools->simple_cmds)
			tools->simple_cmds = cmd;
		else
			; // Add new cmd to the end of the simple_cmds list
		tools->lexer_list = parser_tools.lexer_list;
	}
}
