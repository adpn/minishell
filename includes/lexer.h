/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:01:59 by adupin            #+#    #+#             */
/*   Updated: 2023/10/06 10:57:50 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "struct.h"
# include "minishell.h"

t_lex	*lexer(char *str);
void	print_lex(t_lex *lex);
t_lex	*free_lex_chained(t_lex *lex);
void	free_lex_node(t_lex *lex);
t_lex	*get_element(t_lex *node, int i);

#endif