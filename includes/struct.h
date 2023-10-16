/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:19 by adupin            #+#    #+#             */
/*   Updated: 2023/10/12 10:21:16 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "minishell.h"

enum e_tokens
{
	PIPE = 1,
	R_INPUT,
	R_OUTPUT,
	HEREDOC,
	R_APP,
	WORD
};

/* If operator != WORD, word = NULL */
typedef struct s_lex
{
	char			*word;
	int				operator;
	int				index;
	struct s_lex	*next;
	struct s_lex	*prev;	
}	t_lex;

typedef struct s_parser_tools
{
	t_lex			*lexer_list;
	t_lex			*redirections;
	int				num_redirections;
	struct s_tools	*tools;
}	t_parser_tools;

typedef struct s_tools
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_simple_cmds	*simple_cmds;
	t_lex					*lexer_list;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
	int						*pid;
	bool					heredoc;
	bool					reset;
}	t_tools;

// Structure used for the parser process
typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lex					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

#endif