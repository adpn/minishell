/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:19 by adupin            #+#    #+#             */
/*   Updated: 2023/10/03 15:09:14 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum e_tokens
{
	PIPE = 1,
	R_INPUT,
	R_OUTPUT,
	HEREDOC,
	R_APP,
	WORD
};

/* if word != NULL token = 0, if token != 0 word = NULL */
typedef struct s_lex
{
	char			*word;
	int				operator;
	int				index;
	struct s_lex	*next;
	struct s_lex	*prev;	
}			t_lex;

// Structure used for the parser process
typedef struct s_simple_cmds
{
	char					**str;
	//int						(*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lex					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

#endif