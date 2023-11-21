/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraycopy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:04:04 by adupin            #+#    #+#             */
/*   Updated: 2023/11/07 14:04:00 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**array_copy(char **tab)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_xmalloc(sizeof(char *) * (ft_array_len(tab) + 1));
	while (tab[i])
	{
		new[i] = ft_xstrdup(tab[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
