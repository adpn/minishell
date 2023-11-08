/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:29:30 by adupin            #+#    #+#             */
/*   Updated: 2023/11/08 10:48:28 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	init_variables(int *i, int *ib, t_lex **lex, t_quotes *quotes)
{
	*i = 0;
	*ib = 0;
	lex[0] = NULL;
	quotes->double_q = 0;
	quotes->simple_q = 0;
}

t_lex	*lexer(char *str)
{
	int			i;
	char		*buffer;
	int			ib;
	t_lex		*lex[2];
	t_quotes	quotes;
	
	init_variables(&i, &ib, lex, &quotes);
	buffer = ft_xcalloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		buffer[ib] = str[i];
		ib++;
		update_quotes(&quotes, str[i]);
		if (ft_in_charset(str[i], "|<> ") == true && is_inside_quotes(&quotes) == false)
		{
			buffer[ib - 1] = '\0';
			lex[0] = create_word_node(lex, buffer, ib, 1);
			ib = 0;
			if (str[i] != ' ')
			{
				lex[1] = create_op_node(&str[i]);
				if (lex[1]->operator == HEREDOC || lex[1]->operator == R_APP)
					i++;
				lex[0] = assign_node(lex[0], lex[1]);
			}
		}
		i++;
	}
	lex[0] = create_word_node(lex, buffer, ib, 0);
	free(buffer);
	create_node(NULL, -1);
	return (get_element(lex[0], 0));
}
