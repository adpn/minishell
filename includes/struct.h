/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:19 by adupin            #+#    #+#             */
/*   Updated: 2023/11/23 14:02:28 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct s_tools	t_tools;

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

// Structure used for the parser process
typedef struct s_cmds
{
	char			**args;
	int				(*builtin)(t_tools *, struct s_cmds *);
	int				nb_redirects;
	char			*hd_filename;
	t_lex			*redirects;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_tools
{
	char			**paths;
	struct s_cmds	*cmds;
	t_lex			*lex_list;
	int				pipes;
	int				*pid;
	bool			heredoc;
	int				stop_heredoc;
	int				in_heredoc;
	int				in_cmd;
	bool			reset;
	int				error_code;
}	t_tools;

typedef struct s_quotes
{
	int		simple_q;
	int		double_q;
}	t_quotes;

#endif