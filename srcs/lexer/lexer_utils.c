/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:39:20 by adupin            #+#    #+#             */
/*   Updated: 2023/11/09 11:20:53 by adupin           ###   ########.fr       */
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
