/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:38:25 by alexphil          #+#    #+#             */
/*   Updated: 2023/12/04 11:53:17 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "lexer.h"

void	*ft_xmalloc(size_t size);
void	*ft_xcalloc(size_t count, size_t size);
char	*ft_xstrdup(const char *s1);

int		index_element_environ(char *name);
void	add_element_to_environ(char *name, char *value);
void	replace_element_to_environ(char *name, char *value);
char	*value_var_environ(char *name);
void	delete_var_environ(char *name);
void	init_environ(void);
void	free_environ(void);
void	push_var_to_environ(t_var_env *var_env);

int		ft_array_len(char **array);
char	**array_copy(char **tab);

bool	is_inside_quotes(t_quotes *quotes);
void	update_quotes(t_quotes *quotes, char c);

void	ft_print_error(char *s1, char *s2, char *s3);

// tools.c
t_cmds	*rewind_cmds(t_cmds *cmd);
t_lex	*rewind_lex(t_lex *cmd);
void	free_cmds(t_cmds *cmd);
void	initools(t_tools *tools);
int		resetools(t_tools *tools);

#endif