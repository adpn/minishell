/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_and_split_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:03:59 by adupin            #+#    #+#             */
/*   Updated: 2023/12/04 11:49:09 by adupin           ###   ########.fr       */
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
	str = ft_xcalloc((len_total(tab) + 1), sizeof(char));
	while (tab[i])
	{
		ft_strlcat(str, tab[i], len_total(tab) + 2);
		ft_strlcat(str, "", len_total(tab) + 2);
		i++;
	}
	return (str);
}

static int	ft_count(char *str, char c)
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
	char		**tab;
	int			i;
	int			j;
	t_quotes	quotes;

	quotes = (t_quotes){0, 0};
	tab = ft_xmalloc(sizeof(char *) * (ft_count(str, '$') + 2));
	i = 0;
	j = 0;
	while (str[i])
	{
		update_quotes(&quotes, str[i]);
		if (str[i] == '$' && quotes.simple_q % 2 == 0)
		{
			tab[j] = ft_xmalloc(i + 1);
			ft_strlcpy(tab[j++], str, i + 1);
			str += i;
			i = 0;
		}
		i++;
	}
	tab[j] = ft_xmalloc(i + 1);
	ft_strlcpy(tab[j], str, i + 1);
	tab[j + 1] = NULL;
	return (tab);
}
