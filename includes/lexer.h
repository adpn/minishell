/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:01:59 by adupin            #+#    #+#             */
/*   Updated: 2023/10/11 16:11:04 by alexphil         ###   ########.fr       */
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
void	add_count_quotes(t_quotes *quotes, char *str);
int	is_inside_quote(char *str, t_quotes *quotes);

t_lex	*lexer(char *str);
t_lex	*get_element(t_lex *node, int i);

#endif