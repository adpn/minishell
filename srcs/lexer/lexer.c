/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:29:30 by adupin            #+#    #+#             */
/*   Updated: 2023/10/16 16:56:14 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// t_lex *assign_node(t_lex *lex, t_lex *node, int i)
// {
// 	if (i == 0)
// 	{
// 		node->prev = NULL;
// 		node->next = NULL;
// 	}
// 	else
// 	{
// 		lex->next = node;
// 		node->prev = lex;
// 		node->next = NULL;
// 	}
// 	return (node);
// }

// int	handle_token(char *str, t_lex *lex)
// {
// 	size_t	len;

// 	len = ft_strlen(str);
// 	if (!ft_strncmp(str, "|", len))
// 		lex->operator = PIPE;
// 	else if (!ft_strncmp(str, "<<", len))
// 		lex->operator = HEREDOC;
// 	else if (!ft_strncmp(str, ">>", len))
// 		lex->operator = R_APP;
// 	else if (!ft_strncmp(str, "<", len))
// 		lex->operator = R_INPUT;
// 	else if (!ft_strncmp(str, ">", len))
// 		lex->operator = R_OUTPUT;
// 	else
// 		return (0);
// 	return (1);
// }

/* Return pointer to i node*/
t_lex	*get_element(t_lex *node, int i)
{
	if (i < 0)
		return (NULL);
	if (node->index == i)
		return (node);
	if (node->index > i)
		return (get_element(node->prev, i));
	else
		return (get_element(node->next, i));
}

// int	op_or_word(char *str, t_lex *lex, t_quotes *quotes)
// {
// 	if (!is_inside_quote(str, quotes))
// 	{
// 		if (!handle_token(str, lex))
// 		{
// 			lex->operator = WORD;
// 			lex->word = ft_strdup(str);
// 			if (!lex->word)
// 				return (0);
// 		}
// 		if (lex->operator != 0 && lex->operator != WORD)
// 			lex->word = NULL;
// 	}
// 	else
// 	{
// 		lex->operator = WORD;
// 		lex->word = ft_strdup(str);
// 			if (!lex->word)
// 				return (0);
// 	}
// 	return (1);
// }

// t_lex	*lexer(char *str)
// {
// 	char	**splitted;
// 	int		i;
// 	t_lex	*node;
// 	t_lex	*lex;
// 	t_quotes quotes;

// 	lex = NULL;
// 	quotes.double_q = 0;
// 	quotes.simple_q = 0;
// 	splitted = ft_split(str, ' ');
// 	if (!splitted)
// 		return (NULL);
// 	i = 0;
// 	while (splitted[i])
// 	{
// 		node = malloc(sizeof(t_lex));
// 		if (!node)
// 			return (free_lex_chained(get_element(lex, 0)), ft_free_split(splitted), NULL);
// 		if (!op_or_word(splitted[i], node, &quotes))
// 			return (free_lex_chained(get_element(lex, 0)), free(node),
// 				ft_free_split(splitted), NULL);
// 		node->index = i;
// 		lex = assign_node(lex, node, i);
// 		i++;
// 	}
// 	ft_free_split(splitted);
// 	lex->next = NULL;
// 	return (get_element(lex, 0));
// }

t_lex *get_last(t_lex *lex)
{
	if (!lex)
		return (NULL);
	while (lex)
	{
		if (!lex->next)
			return (lex);
		lex = lex->next;
	}
	return (lex);
}

char	*op_pos(char *str, int op)
{
	size_t	len;

	len = ft_strlen(str);
	if (op == HEREDOC)
		return (ft_strnstr(str, "<<", len));
	else if (op == R_APP)
		return (ft_strnstr(str, ">>", len));
	else if (op == R_INPUT)
		return (ft_strnstr(str, "<", len));
	else if (op == R_OUTPUT)
		return (ft_strnstr(str, ">", len));
	else if (op == PIPE)
		return (ft_strnstr(str, "|", len));
	else
		return (NULL);
}

int	has_operator(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (ft_strnstr(str, "<<", len))
		return (HEREDOC);
	else if (ft_strnstr(str, ">>", len))
		return (R_APP);
	else if (ft_strnstr(str, "<", len))
		return(R_INPUT);
	else if (ft_strnstr(str, ">", len))
		return(R_OUTPUT);
	else if (ft_strnstr(str, "|", len))
		return (PIPE);
	else
		return (WORD);	
}
t_lex *create_node(char *str, int *node_index)
{
	t_lex *node;
	t_lex *new;
	int op;

	node = malloc(sizeof(t_lex));
	if (!node)
		return (NULL);
	op = has_operator(str);
	node->index = *node_index;
	*node_index += 1;
	printf("str = %s\nop = %d\n", str, op);
	node->next = NULL;
	if (op == WORD)
	{
		node->word = ft_strdup(str);
		if (!node->word)
			return(free(node), NULL);
		node->operator = WORD;
	}
	else
	{
		node->word = ft_substr(str, 0, op_pos(str, op) - str);
		if (!node->word)
			return(free(node), NULL);
		if(node->word[0] == '\0')
		{
			free(node->word);
			node->word = NULL;
			node->operator = op;
			if (op == HEREDOC || op == R_APP)
				new = create_node(str + 2, node_index);
			else
				new = create_node(str + 1, node_index);
		}
		else
		{
			new = create_node(str + ft_strlen(node->word), node_index);
		}
		if (!new)
			return (free(node), NULL);
		node->next = new;
		new->prev = node;
		new->next = NULL;
	}
	return (node);
}

t_lex	*lexer(char *str)
{
	char	**splitted;
	int		i;
	int		node_index;
	t_lex	*node;
	t_lex	*lex;
	t_quotes quotes;

	lex = NULL;
	quotes.double_q = 0;
	quotes.simple_q = 0;
	splitted = ft_split(str, ' ');
	if (!splitted)
		return (NULL);
	i = 0;
	node_index = 0;
	while (splitted[i])
	{
		node = create_node(splitted[i], &node_index);
		if (!node)
			return (0);
		if (!lex)
		{
			lex = node;
			lex->prev = NULL;
		}
		else
		{
			lex->next = node;
			node->prev = lex;
			lex = get_last(node);
		}
		i++;
	}
	ft_free_split(splitted);
	return (get_element(lex, 0));
}
