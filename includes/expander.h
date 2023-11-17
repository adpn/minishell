/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:02:10 by adupin            #+#    #+#             */
/*   Updated: 2023/11/17 16:19:40 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include "utils.h"

char	*get_dollar(char *str);
char	*get_var_name(char *str);
char	*get_value(char *name, t_tools *tools);

char	*complete_string(char *str, t_tools *tools);
int	expand(char **str, t_tools *tools);

#endif