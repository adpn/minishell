/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:37:06 by adupin            #+#    #+#             */
/*   Updated: 2023/10/09 12:54:28 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*has_dollar(char *str)
{
	return (ft_strchr(str, '$'));
}

int	get_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*name;

	i = 1;
	while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\t')
		i++;
	name = ft_substr(str, 1, i - 1);
	if (!name)
		return (NULL);
	return (name);
}

char	*complete_string(char *str)
{
	char	*new;
	char	*value;
	char	*name;
	int		i;

	while (has_dollar(str))
	{
		i = get_index(str, '$');
		name = get_var_name(ft_strchr(str, '$'));
		if (!name)
			return (NULL);
		value = getenv(name);
		if (!value)
			value = "";
		new = malloc(ft_strlen(str) - ft_strlen(name) + ft_strlen(value) + 1);
		if (!new)
			return (free(name), NULL);
		ft_strlcpy(new, str, i + 1);
		ft_strlcat(new, value, ft_strlen(new) + ft_strlen(value) + 1);
		ft_strlcat(new, &str[i + ft_strlen(name) + 1], ft_strlen(new) + ft_strlen(&str[i + ft_strlen(name)]) + 1);
		free(str);
		free(name);
		str = new;
	}
	return(str);
}
//Return 1 if success, 0 if malloc failed
int	expand(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (has_dollar(str[i]))
		{
			str[i] = complete_string(str[i]);
			if (!str[i])
				return (0);
		}
		i++;
	}
	return (1);
}
