/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:37:06 by adupin            #+#    #+#             */
/*   Updated: 2023/12/04 11:07:06 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*copy_new_string(char *str, char *name, char *value)
{
	char	*new;

	new = ft_xmalloc((ft_strlen(str) - ft_strlen(name) + ft_strlen(value)) * sizeof(char));
	ft_strlcpy(new, value, ft_strlen(value) + 1);
	ft_strlcat(new, &str[ft_strlen(name) + 1],
		ft_strlen(new) + ft_strlen(&str[ft_strlen(name)]) + 1);
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

char	*replace_dollar(char *str, t_tools *tools)
{
	char	*new;
	char	*value;
	char	*name;

	name = get_var_name(str);
	if (!name)
		return (NULL);
	value = get_value(name, tools);
	if (!value)
		return (free(name), NULL);
	new = copy_new_string(str, name, value);
	if (name[0] == '?')
		free(value);
	free(str);
	free(name);
	str = new;
	return (str);
}

char	*complete_clean(char *str, t_tools *tools)
{
	char		**tab;
	int			i;
	char 		*new;

	tab = split_on_dollar(str);
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '$')
		{
			tab[i] = replace_dollar(tab[i], tools);
		}
		i++;
	}
	new = cat_all_in_one(tab);
	ft_free_split(tab);
	free(str);
	return (new);
}

//Return 1 if success, 0 if malloc failed
int	expand(char **tab, t_tools *tools)
{
	int	i;

	i = 0;
	while (tab[i])
	{

		tab[i] = complete_clean(tab[i], tools);
		i++;
	}
	remove_empty_string(tab);
	return (1);
}
