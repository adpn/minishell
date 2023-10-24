/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:39:20 by adupin            #+#    #+#             */
/*   Updated: 2023/10/24 16:25:03 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_lex(t_lex *lex)
{
	if (lex == NULL)
		return ;
	if (lex->operator == WORD)
		printf("WORD = %s\n", lex->word);
	else
		printf("%i\n", lex->operator);
	print_lex(lex->next);
}
/* Return pointer to i node*/
t_lex	*get_element(t_lex *node, int i)
{
	if (i < 0 || node == NULL)
		return (NULL);
	if (node->index == i)
		return (node);
	if (node->index > i)
		return (get_element(node->prev, i));
	else
		return (get_element(node->next, i));
}

bool is_inside_quotes(t_quotes *quotes)
{
	if (quotes->double_q % 2 == 1 || quotes->simple_q % 2 == 1)
		return (true);
	return (false);
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