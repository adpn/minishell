/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:19 by adupin            #+#    #+#             */
/*   Updated: 2023/10/27 14:41:43 by adupin           ###   ########.fr       */
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
	void			(*builtin)(t_tools *, struct s_cmds *);
	int				nb_redirects;
	t_lex			*redirects;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

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
	int				error_code;
}	t_tools;

typedef struct	s_var_env
{
	char	*name;
	char	*value;
}				t_var_env;

#endif