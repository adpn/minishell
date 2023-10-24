/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:23:36 by adupin            #+#    #+#             */
/*   Updated: 2023/10/24 16:24:46 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Free only this node*/
void	free_lex_node(t_lex *lex)
{
	if (lex == NULL)
		return ;
	if (lex->word)
		free(lex->word);
	free(lex);
}

/*Free all the following chained list*/
t_lex	*free_lex_chained(t_lex *lex)
{
	if (lex == NULL)
		return (NULL);
	free_lex_chained(lex->next);
	free_lex_node(lex);
	return (NULL);
}
