/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:46:55 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/12 14:01:27 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_cmds	*init_cmd(t_parser_tools *parser_tools)
{
	char	**str;
	int		i;
	int		args;
	
	i = 0;
	// remove_redirect()
	args = count_args(parser_tools->lex_list);
	str = ft_calloc(args + 1, sizeof(char *));
	if (!str)
		// Unified error management
	while (args > 0)
	{
		if (parser_tools->lex_list->word)
		{
			str[i++] = ft_strdup(parser_tools->lex_list->word);
			// lexerdelone() at index i
		}
		args--;
	}
	// return new_cmd()
}

int	parser(t_tools *tools)
{
	t_simple_cmds	*node;
	t_parser_tools	parser_tools;

	tools->simple_cmds = NULL;
	count_pipes(tools->lex_list, tools);
	while (tools->lex_list)
	{
		if (tools->lex_list && tools->lex_list->operator == PIPE)
			; // delete current node from lexer list (being a pipe)
		parser_tools = init_parser_tools(tools->lex_list, tools);
		node = init_cmd(&parser_tools); // WIP
		if (!node)
			; // unified error management
		if (!tools->simple_cmds)
			tools->simple_cmds = node;
		else
			; // Add new cmd to the end of the simple_cmds list
		tools->lex_list = parser_tools.lex_list;
	}
}
