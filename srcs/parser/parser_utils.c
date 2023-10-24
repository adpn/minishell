/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:50:34 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/24 09:44:55 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_pipes(t_lex *lex)
{
	t_lex	*tmp;
	int		i;

	tmp = lex;
	i = 0;
	while (tmp)
	{
		if (lex->operator == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	count_redirects(t_lex *lex)
{
	t_lex	*tmp;
	int		i;

	tmp = lex;
	i = 0;
	while (tmp && tmp->operator != PIPE)
	{
		if (lex->operator >= R_APP && lex->operator <= R_OUTPUT)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	count_args(t_lex *lex)
{
	t_lex	*tmp;
	int		i;

	tmp = lex;
	i = 0;
	while (tmp->word)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
