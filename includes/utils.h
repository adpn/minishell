/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:38:25 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/23 10:37:43 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "minishell.h"

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
int	ft_array_len(char **array);
char	**array_copy(char **tab);

bool is_inside_quotes(t_quotes *quotes);
void	update_quotes(t_quotes *quotes, char c);

bool	ft_in_charset(char c, char *charset);
void	ft_print_error(char *s1, char *s2, char *s3);
#endif