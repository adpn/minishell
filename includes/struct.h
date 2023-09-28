/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:18:19 by adupin            #+#    #+#             */
/*   Updated: 2023/09/28 13:53:36 by adupin           ###   ########.fr       */
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
	R_APP
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

#endif