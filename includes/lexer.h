/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:01:59 by adupin            #+#    #+#             */
/*   Updated: 2023/10/23 12:40:13 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "struct.h"
# include "minishell.h"

typedef struct s_quotes
{
	int		simple_q;
	int		double_q;
}	t_quotes;

/* lexer_utils.c */
void	print_lex(t_lex *lex);
t_lex	*free_lex_chained(t_lex *lex);
void	free_lex_node(t_lex *lex);
t_lex	*get_element(t_lex *node, int i);
bool	is_inside_quotes(t_quotes *quotes);
t_lex	*lexer(char *str);

#endif