/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:39:20 by adupin            #+#    #+#             */
/*   Updated: 2023/10/02 12:16:24 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Free only this node*/
void	free_struct(t_lex *lex)
{
	if (lex == NULL)
		return ;
	if (lex->word)
		free(lex->word);
	free(lex);
}

/*Free all the following chained list*/
t_lex	*free_lex(t_lex *lex)
{
	if (lex == NULL)
		return (NULL);
	free_lex(lex->next);
	free_struct(lex);
	return (NULL);
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
