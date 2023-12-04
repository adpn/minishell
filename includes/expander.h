/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:02:10 by adupin            #+#    #+#             */
/*   Updated: 2023/12/04 11:05:43 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include "utils.h"

char	*get_dollar(char *str);
char	*get_var_name(char *str);
char	*get_value(char *name, t_tools *tools);

char	**split_on_dollar(char *str);
char	*cat_all_in_one(char **tab);

char	*complete_clean(char *str, t_tools *tools);
int		expand(char **str, t_tools *tools);

#endif