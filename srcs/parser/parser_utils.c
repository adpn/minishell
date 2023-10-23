/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:50:34 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/16 16:50:55 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (tmp)
	{
		if (lex->operator >= HEREDOC && lex->operator <= R_APP)
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
	while (lex->word)
		i++;
	return (i);
}
