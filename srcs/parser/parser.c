/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:46:55 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/11 10:52:15 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
