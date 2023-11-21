/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:01:59 by adupin            #+#    #+#             */
/*   Updated: 2023/11/08 10:48:02 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "struct.h"
# include "utils.h"

/* lexer_free.c */
t_lex	*free_lex_chained(t_lex *lex);
void	free_lex_node(t_lex *lex);

/* lexer_utils.c */
void	print_lex(t_lex *lex);
t_lex	*get_element(t_lex *node, int i);
bool	ft_in_charset(char c, char *charset);

/* lexer.c */
t_lex	*lexer(char *str);

/* nodes.c */
t_lex *create_node(char *str, int type);
t_lex *create_op_node(char *str);
t_lex *create_word_node(t_lex **lex, char *buffer, int ib, int condition);
t_lex *assign_node(t_lex *lex, t_lex *node);

#endif