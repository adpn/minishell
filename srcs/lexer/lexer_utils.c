/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:39:20 by adupin            #+#    #+#             */
/*   Updated: 2023/10/16 16:43:25 by adupin           ###   ########.fr       */
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

static void	add_count_quotes(t_quotes *quotes, char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			quotes->double_q++;
		else if (str[i] == '\'')
			quotes->simple_q++;
		i++;
	}
}

int	is_inside_quote(char *str, t_quotes *quotes)
{
	add_count_quotes(quotes, str);
	if ((ft_strchr(str, '\'') || ft_strchr(str, '\"'))|| (quotes->double_q % 2 == 1 || quotes->simple_q % 2 == 1))
		return (1);
	return (0);
}
