/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:46:55 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/10 12:01:02 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_lex	*has_pipe(t_lex *lex)
{
	while (lex)
	{
		if (lex->operator == PIPE)
			return (lex);
		lex = lex->next;
	}
	return (NULL);
}

void	has_redirect(t_lex *lex)
{
	;
}

void	set_redirect(t_lex *lex, t_simple_cmds *cmds)
{
	;
}

void	parser(t_lex *lex)
{
	t_simple_cmds	*cmds;

	
}
