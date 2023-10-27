/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:26:04 by adupin            #+#    #+#             */
/*   Updated: 2023/10/27 15:30:20 by adupin           ###   ########.fr       */
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

int	index_element_environ(char *name)
{
	extern char	**environ;
	int		i;
	int		len;

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

char *value_var_environ(char *name)
{
	extern char	**environ;
	int		i;
	int		len;

	i = index_element_environ(name);
	if (i == -1)
		return (NULL);
	len = ft_strlen(name);
	return (environ[i] + len + 1);
}

static char	*create_element(char *name, char *value)
{
	int	len_element;
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
	extern char **environ;
	char **new;
	int	i;
	int	len_array;
	
	i = 0;
	printf("%s %s\n", name, value);
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
	extern char **environ;
	int	i;
	int	len_element;
	
	i = index_element_environ(name);
	len_element = ft_strlen(name) + ft_strlen(value) + 2;
	// free(environ[i]);
	environ[i] = create_element(name, value);
}

