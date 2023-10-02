/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:29:30 by adupin            #+#    #+#             */
/*   Updated: 2023/10/02 16:31:10 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

int	test_operator(t_lex *lex, char *str, char *op, size_t len)
{
	if (ft_strnstr(str, op, len))
	{
		if (len > ft_strlen(op))
		{
			lex->check = -1;
			return (0);
		}
		return (1);
	}
	
	return (0);
}

int	op_or_word(char *str, t_lex *lex)
{
	size_t	len;

	len = ft_strlen(str);
	if (test_operator(lex, str, "|", len)) // utiliser ft_strncmp
		lex->operator = PIPE;
	else if (test_operator(lex, str, "<<", len))
		lex->operator = HEREDOC;
	else if (test_operator(lex, str, ">>", len))
		lex->operator = R_APP;
	else if (test_operator(lex, str, "<", len))
		lex->operator = R_INPUT;
	else if (test_operator(lex, str, ">", len))
		lex->operator = R_OUTPUT;
	else if (lex->check == -1)
		return (0);
	else
	{
		lex->operator = WORD;
		lex->word = ft_strdup(str);
		if (!lex->word)
			return (0);
	}
	if (lex->operator != 0 && lex->operator != WORD)
		lex->word = NULL;
	return (1);
}

t_lex	*lexer(char *str)
{
	char	**splitted;
	int		i;
	t_lex	*node;
	t_lex	*lex;

	lex = NULL;
	splitted = ft_split(str, ' ');
	if (!splitted)
		return (NULL);
	i = 0;
	while (splitted[i])
	{
		node = malloc(sizeof(t_lex));
		if (!node)
			return (free_lex(get_element(lex, 0)), ft_free_split(splitted), NULL);
		node->check = 0;
		if (!op_or_word(splitted[i], node))
			return (free_lex(get_element(lex, 0)), free(node),
				ft_free_split(splitted), NULL);
		node->index = i;
		if (i == 0)
		{
			lex = node;
			lex->prev = NULL;
			lex->next = NULL;
		}
		else
		{
			lex->next = node;
			node->prev = lex;
			node->next = NULL;
			lex = node;
		}
		i++;
	}
	ft_free_split(splitted);
	lex->next = NULL;
	return (get_element(lex, 0));
}
