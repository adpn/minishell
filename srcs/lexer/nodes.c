/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:25:39 by adupin            #+#    #+#             */
/*   Updated: 2023/11/17 15:25:26 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lex	*assign_node(t_lex *lex, t_lex *node)
{
	if (lex == NULL)
	{
		node->prev = NULL;
		node->next = NULL;
	}
	else
	{
		lex->next = node;
		node->prev = lex;
		node->next = NULL;
	}
	return (node);
}

/* Type -1 resets the node_index */
t_lex	*create_node(char *str, int type)
{
	static int	node_index = 0;
	t_lex		*node;

	if (type == -1)
	{
		node_index = 0;
		return (NULL);
	}
	node = ft_xmalloc(sizeof(t_lex));
	node->index = node_index;
	node->operator = type;
	node->word = NULL;
	if (type == WORD)
	{
		node->word = ft_xstrdup(str);
	}
	node_index++;
	return (node);
}

t_lex	*create_op_node(char *str)
{
	t_lex	*node;

	node = NULL;
	if (str[0] == '|')
		node = create_node(str, PIPE);
	else if (str[0] == '<')
	{
		if (str[1] && str[1] == '<')
			node = create_node(str, HEREDOC);
		else
			node = create_node (str, R_INPUT);
	}
	else if (str[0] == '>')
	{
		if (str[1] && str[1] == '>')
			node = create_node(str, R_APP);
		else
			node = create_node(str, R_OUTPUT);
	}
	return (node);
}

t_lex	*create_word_node(t_lex **lex, char *buffer, int ib, int condition)
{
	if (ib > condition)
	{
		lex[1] = create_node(buffer, WORD);
		ft_bzero(buffer, ft_strlen(buffer));
		lex[0] = assign_node(lex[0], lex[1]);
	}
	return (lex[0]);
}
