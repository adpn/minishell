/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:29:30 by adupin            #+#    #+#             */
/*   Updated: 2023/10/23 17:02:43 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lex *assign_node(t_lex *lex, t_lex *node)
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

bool	ft_in_charset(char c, char *charset)
{
	int	i;
	
	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (true);
		i++;
	}
	return (false);
}
/* Type -1 resets the node_index */
t_lex *create_node(char *str, int type)
{
	static int node_index = 0;
	t_lex *node;

	if (type == -1)
	{
		node_index = 0;
		return (NULL);
	}
	node = malloc(sizeof(t_lex));
	if (!node)
		return (NULL);
	node->index = node_index;
	node->operator = type;
	node->word = NULL;
	//printf("str = %s\nop = %d\n", str, type);
	if (type == WORD)
	{
		node->word = ft_strdup(str);
		if (!node->word)
			return(free(node), NULL);
	}
	node_index++;
	return (node);
}
t_lex *create_op_node(char *str)
{
	t_lex *node;

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

t_lex	*lexer(char *str)
{
	int			i;
	char		*buffer;
	int			ib;
	t_lex		*lex;
	t_lex		*node;
	t_quotes	quotes;
	
	i = 0;
	ib = 0;
	quotes.double_q = 0;
	quotes.simple_q = 0;
	lex = NULL;
	buffer = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		buffer[ib] = str[i];
		//printf("buffer = %s %i\n", buffer, ib);
		ib++;
		if (str[i] == '\'')
			quotes.simple_q++;
		else if (str[i] == '\"')
			quotes.double_q++;
		else if (ft_in_charset(str[i], "|<> ") == true && is_inside_quotes(&quotes) == false)
		{
			buffer[ib - 1] = '\0';
			if (ib > 1)
			{
				node = create_node(buffer, WORD);
				if (!node)
					return (0);
				ft_bzero(buffer, ft_strlen(str));
				lex = assign_node(lex, node);
			}
			ib = 0;
			if (str[i] != ' ')
			{
				node = create_op_node(&str[i]);
				if (!node)
					return (0);
				if (node->operator == HEREDOC || node->operator == R_APP)
					i++;
				lex = assign_node(lex, node);
			}
		}
		i++;
	}
	if (ib > 0)
	{
		node = create_node(buffer, WORD);
		if (!node)
			return (0);
		lex = assign_node(lex, node);
	}
	free(buffer);
	create_node(NULL, -1);
	return (get_element(lex, 0));
}
