/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_environ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:21:34 by adupin            #+#    #+#             */
/*   Updated: 2023/11/23 10:48:11 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*create_element(char *name, char *value)
{
	int		len_element;
	char	*new;

	len_element = ft_strlen(name) + ft_strlen(value) + 2;
	new = ft_xcalloc(len_element, sizeof(char));
	ft_strlcat(new, name, len_element);
	ft_strlcat(new, "=", len_element);
	ft_strlcat(new, value, len_element);
	return (new);
}

void	add_element_to_environ(char *name, char *value)
{
	extern char	**environ;
	char		**new;
	int			i;
	int			len_array;

	i = 0;
	len_array = ft_array_len(environ);
	new = ft_xmalloc(sizeof(char *) * (len_array + 2));
	while (i < len_array)
	{
		new[i] = environ[i];
		i++;
	}
	new[i] = create_element(name, value);
	new[i + 1] = NULL;
	free(environ);
	environ = new;
}

void	replace_element_to_environ(char *name, char *value)
{
	extern char	**environ;
	int			i;
	int			len_element;

	i = index_element_environ(name);
	if (i == -1)
		return ;
	len_element = ft_strlen(name) + ft_strlen(value) + 2;
	free(environ[i]);
	environ[i] = create_element(name, value);
}

void	delete_var_environ(char *name)
{
	extern char	**environ;
	int			i;
	int			len_array;

	i = index_element_environ(name);
	if (i == -1)
		return ;
	len_array = ft_array_len(environ);
	free(environ[i]);
	while (i < len_array - 1)
	{
		environ[i] = environ[i + 1];
		i++;
	}
	environ[i] = NULL;
}
