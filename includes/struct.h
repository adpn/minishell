/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:19 by adupin            #+#    #+#             */
/*   Updated: 2023/10/23 17:10:19 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "minishell.h"

//The order is important do not change it !
enum e_tokens
{
	PIPE = 1,
	HEREDOC,
	R_APP,
	R_INPUT,
	R_OUTPUT,
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
	t_lex			*lex_list;
	t_lex			*redirections;
	int				num_redirections;
	struct s_tools	*tools;
}	t_parser_tools;

typedef struct s_tools
{
	char			*args;
	char			**paths;
	char			**envp;
	struct s_cmds	*cmds;
	t_lex			*lex_list;
	char			*pwd;
	char			*old_pwd;
	int				pipes;
	int				*pid;
	bool			heredoc;
	bool			reset;
}	t_tools;

// Structure used for the parser process
typedef struct s_cmds
{
	char			**args;
	int				(*builtin)(t_tools *, struct s_simple_cmds *);
	int				nb_redirects;
	t_lex			*redirects;
	struct s_cmds	*next;
}	t_cmds;

#endif