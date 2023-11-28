/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:16:54 by adupin            #+#    #+#             */
/*   Updated: 2023/11/27 11:43:37 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*get_dollar(char *str)
{
	t_quotes	quotes;
	int			i;

	quotes.double_q = 0;
	quotes.simple_q = 0;
	i = -1;
	while (str[++i])
	{
		update_quotes(&quotes, str[i]);
		if (str[i] == ('$') && !(quotes.simple_q % 2))
			return (&((char *)str)[i]);
	}
	return (0);
}

/* Get variable name to expand: starting with $*/
char	*get_var_name(char *str)
{
	int		i;
	char	*name;

	i = 1;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	if (str[1] && str[1] == '?')
		name = ft_xstrdup("?");
	else
		name = ft_substr(str, 1, i - 1);
	if (!name)
		return (NULL);
	return (name);
}

char	*get_value(char *name, t_tools *tools)
{
	char	*value;

	if (name[0] == '?')
	{
		name[1] = '\0';
		value = ft_itoa(tools->error_code);
		if (!value)
			return (NULL);
	}
	else
		value = value_var_environ(name);
	if (!value)
		value = "";
	return (value);
}
