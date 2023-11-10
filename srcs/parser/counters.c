/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:50:34 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/09 11:47:02 by alexphil         ###   ########.fr       */
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
		if (tmp->operator == PIPE)
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
		if (tmp->operator >= HEREDOC && tmp->operator <= R_OUTPUT)
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
	while (tmp && tmp->operator != PIPE)
	{
		if (tmp->word)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
