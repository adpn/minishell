/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:37:06 by adupin            #+#    #+#             */
/*   Updated: 2023/11/28 12:18:45 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	len_total(char **tab)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (tab[i])
	{
		len += ft_strlen(tab[i]);
		i++;
	}
	return (len);
}

char	*cat_all_in_one(char **tab)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_xcalloc((len_total(tab) + 1) * sizeof(char));
	while (tab[i])
	{
		ft_strlcat(str, tab[i], len_total(tab) + 2);
		ft_strlcat(str, "", len_total(tab) + 2);
		i++;
	}
	return (str);
}

char	*copy_new_string(char *str, char *name, char *value)
{
	char	*new;

	new = ft_xmalloc(ft_strlen(str) - ft_strlen(name) + ft_strlen(value) + 1);
	ft_strlcpy(new, str, str + 1);
	ft_strlcat(new, value, ft_strlen(new) + ft_strlen(value) + 1);
	ft_strlcat(new, &str[str + ft_strlen(name) + 1],
		ft_strlen(new) + ft_strlen(&str[str + ft_strlen(name)]) + 1);
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

int	ft_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count += 1;
		i++;
	}
	return (count);
}

char	**split_on_dollar(char *str)
{
	char	**tab;
	int		i;
	int		j;
	t_quotes	quotes;

	tab = ft_xmalloc(sizeof(char *) * (ft_count(str, '$') + 2));
	i = 0;
	j = 0;
	while (str[i])
	{
		update_quotes(&quotes, str[i]);
		if (str[i] == '$' && quotes.simple_q % 2 == 0)
		{
			tab[j] = ft_xmalloc(i + 1);
			ft_strlcpy(tab[j], str, i + 1);
			str += i;
			j++;
			i = 0;
		}
		i++;
	}
	tab[j] = ft_xmalloc(i + 1);
	ft_strlcpy(tab[j], str, i + 1);
	tab[j + 1] = NULL;
	return (tab);
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
