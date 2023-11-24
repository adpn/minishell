/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:37:06 by adupin            #+#    #+#             */
/*   Updated: 2023/11/24 14:53:46 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*copy_new_string(char *str, char *name, char *value, char *dol)
{
	char	*new;

	new = ft_xmalloc(ft_strlen(str) - ft_strlen(name) + ft_strlen(value) + 1);
	ft_strlcpy(new, str, (dol - str) + 1);
	ft_strlcat(new, value, ft_strlen(new) + ft_strlen(value) + 1);
	ft_strlcat(new, &str[(dol - str) + ft_strlen(name) + 1],
		ft_strlen(new) + ft_strlen(&str[(dol - str) + ft_strlen(name)]) + 1);
	return (new);
}

void	remove_empty_string(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '\0')
		{
			free(tab[i]);
			j = i;
			while (tab[j])
			{
				tab[j] = tab[j + 1];
				j++;
			}
			tab[j] = NULL;
		}
		i++;
	}
}

char	*complete_string(char *str, t_tools *tools)
{
	char	*new;
	char	*value;
	char	*name;
	char	*dol;

	while (get_dollar(str))
	{
		dol = get_dollar(str);
		name = get_var_name(dol);
		if (!name)
			return (NULL);
		value = get_value(name, tools);
		if (!value)
			return (NULL);
		new = copy_new_string(str, name, value, dol);
		if (name[0] == '?')
			free(value);
		free(str);
		free(name);
		str = new;
	}
	return (str);
}

//Return 1 if success, 0 if malloc failed
int	expand(char **tab, t_tools *tools)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (get_dollar(tab[i]))
		{
			tab[i] = complete_string(tab[i], tools);
			if (!tab[i])
				return (0);
		}
		i++;
	}
	remove_empty_string(tab);
	return (1);
}
