/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:46:55 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/03 11:21:13 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	has_pipe(t_lex *lex)
{
	while (lex)
	{
		if (lex->operator == PIPE)
			return (1);
		lex = lex->next;
	}
	return (0);
}

void	parser(t_lex *lex)
{
	t_simple_cmds	*cmds;
	int				has_redirect;

	while (lex != PIPE)
	{
		if (lex->operator)
			
	}
}
