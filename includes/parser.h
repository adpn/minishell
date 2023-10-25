/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:01:42 by adupin            #+#    #+#             */
/*   Updated: 2023/10/25 11:52:17 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"
# include "utils.h"

// Counters
int		count_pipes(t_lex *lex);
int		count_redirects(t_lex *lex);
int		count_args(t_lex *lex);

// Redirects
void	get_redirects(t_tools *tools, t_cmds *cmd);
void	new_redirect(t_tools *tools, t_cmds *cmd);
void	add_redirect(t_cmds *cmd, t_lex *redirect);

// Cmds
void	init_cmd(t_cmds *cmd);
void	new_cmd(t_tools *tools);
void	add_cmd(t_tools *tools, t_cmds *cmd);

// Parser
void	syntax_check(t_tools *tools);
void	parser(t_tools *tools);

// Print
void	redirects_display(t_lex	*redirects);
void	args_display(char **args);
void	cmds_display(t_cmds *cmds);
void	parser_display(t_tools *tools);

#endif