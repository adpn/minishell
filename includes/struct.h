/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:19 by adupin            #+#    #+#             */
/*   Updated: 2023/10/23 13:41:01 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum e_tokens
{
	PIPE = 1,
	HEREDOC,
	R_INPUT,
	R_OUTPUT,
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
	struct s_cmds	*prev;
}	t_cmds;

#endif