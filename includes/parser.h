/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:01:42 by adupin            #+#    #+#             */
/*   Updated: 2023/10/12 13:40:01 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"
# include "minishell.h"

// Utils
t_parser_tools	init_parser_tools(t_lex *lex_list, t_tools *tools);
void			count_pipes(t_lex *node, t_tools *tools);
int				count_args(t_lex *node);
t_lex			*get_next_cmd(t_lex *node);

// Parser
t_simple_cmds	*init_cmd(t_parser_tools *parser_tools);
int				parser(t_tools *tools);

#endif