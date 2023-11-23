/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:26:04 by adupin            #+#    #+#             */
/*   Updated: 2023/11/23 10:47:55 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	index_element_environ(char *name)
{
	extern char	**environ;
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(name);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*value_var_environ(char *name)
{
	extern char	**environ;
	int			i;
	int			len;

	i = index_element_environ(name);
	if (i == -1)
		return (NULL);
	len = ft_strlen(name);
	return (environ[i] + len + 1);
}

void	init_environ(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		environ[i] = ft_xstrdup(environ[i]);
		i++;
	}
}

void	free_environ(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		free(environ[i]);
		i++;
	}
	free(environ);
}
