/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:29:30 by adupin            #+#    #+#             */
/*   Updated: 2023/09/28 14:18:50 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_lex(t_lex *lex)
{
	if (lex == NULL)
		return ;
	free_lex(lex->next);
	if (lex->word)
		free(lex->word);
	free(lex);
}

void	print_lex(t_lex *lex)
{
	if (lex == NULL)
		return ;
	if (lex->operator != 0)
		printf("%i\n", lex->operator);
	else
		printf("%s\n", lex->word);
	print_lex(lex->next);
}
/* Return pointer to i element*/
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

int	token_or_word(char *str, t_lex *lex)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strnstr(str, "|", len))
	{
		if (len > 1)
			return (0);
		lex->operator = PIPE;
	}
	else if (ft_strnstr(str, "<<", len))
	{
		if (len > 2)
			return (0);
		lex->operator = HEREDOC;
	}
	else if (ft_strnstr(str, ">>", len))
	{
		if (len > 2)
			return (0);
		lex->operator = R_APP;
	}
	else if (ft_strnstr(str, "<", len))
	{
		if (len > 1)
			return (0);
		lex->operator = R_INPUT;
	}
	else if (ft_strnstr(str, ">", len))
	{
		if (len > 1)
			return (0);
		lex->operator = R_OUTPUT;
	}
	else
	{
		lex->operator = 0;
		lex->word = ft_strdup(str);
		if (!lex->word)
			return (0);
	}
	if (lex->operator != 0)
		lex->word = NULL;
	return (1);
}

t_lex	*lexer(char *str)
{
	char	**splitted;
	int		i;
	t_lex	*node;
	t_lex	*lex;

	splitted = ft_split(str, ' ');
	if (!splitted)
		return (NULL);
	i = 0;
	while (splitted[i])
	{
		node = malloc(sizeof(t_lex));
		if (!node)
			return (NULL);
		if (!token_or_word(splitted[i], node))
			return (NULL);
		node->index = i;
		if (i == 0)
			lex = node;
		else
		{
			lex->next = node;
			node->prev = lex;
			lex = node;
		}
		i++;
	}
	ft_free_split(splitted);
	lex->next = NULL;
	return (get_element(lex, 0));
}


