/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:37:06 by adupin            #+#    #+#             */
/*   Updated: 2023/11/08 10:58:21 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*get_dollar(char *str)
{
	t_quotes quotes;
	int	i;

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
/* Get variable name to expand: starting with $*/
char	*get_var_name(char *str)
{
	int		i;
	char	*name;

	i = 1;
	while (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != '\t')
		i++;
	if (str[1] && str[1] == '?')
		name = ft_xstrdup("?");
	else
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
	char	*dol;

	while (get_dollar(str))
	{
		dol = get_dollar(str);
		name = get_var_name(dol);
		if (!name)
			return (NULL);
		if (ft_strncmp("?", name, ft_strlen(name)) == 0) // TO CHECK, $? with anything behind is supposed to work
		{
			value = NULL;
			printf("Hello need exit status here\n");
		}
		else
			value = value_var_environ(name);
		if (!value)
			value = "";
		new = ft_xmalloc(ft_strlen(str) - ft_strlen(name) + ft_strlen(value) + 1);
		// if (!new)
		// 	return (free(name), NULL);
		ft_strlcpy(new, str, (dol - str) + 1);
		ft_strlcat(new, value, ft_strlen(new) + ft_strlen(value) + 1);
		ft_strlcat(new, &str[(dol - str) + ft_strlen(name) + 1], ft_strlen(new) + ft_strlen(&str[(dol - str) + ft_strlen(name)]) + 1);
		free(str);
		free(name);
		str = new;
	}
	return(str);
}
//Return 1 if success, 0 if malloc failed
int	expand(char **str)
{
	extern char **environ;
	//need to use it
	
	int	i;

	i = 0;
	while (str[i])
	{
		if (get_dollar(str[i]))
		{
			str[i] = complete_string(str[i]);
			if (!str[i])
				return (0);
		}
		i++;
	}
	return (1);
}
