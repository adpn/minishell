/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:16:57 by adupin            #+#    #+#             */
/*   Updated: 2023/11/06 15:27:58 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	push_var_to_environ(t_var_env *var_env)
{
	char	*value;

	value = var_env->value;
	if (!value)
		value = "";
	if (index_element_environ(var_env->name) == -1)
		add_element_to_environ(var_env->name, value);
	else
		replace_element_to_environ(var_env->name, value);
}

static char	*get_value(char *str)
{
	char	*value;
	int		i;
	int		j;
	
	if (!str || !str[0])
		return (NULL);
	str = str + 1;
	value = ft_xmalloc(ft_strlen(str) * sizeof(char) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
			value[j++] = str[i];
		i++;
	}
	value[j] = '\0';
	return (value);
}

static char	*get_name(char *str)
{
	char	*name;
	int		i;
	int		j;
	
	name = ft_xmalloc(ft_strlen(str) * sizeof (char) + 1);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ')
			return (free(name), NULL);
		if (str[i] != '\"' && str[i] != '\'')
			name[j++] = str[i];
		i++;
	}
	name[j] = '\0';
	if (ft_isdigit(name[0]))
		return (free(name), NULL);
	return (name);
}

void	ft_export(t_tools *tools, t_cmds *cmds)
{
	t_var_env	var_env;
	int		i;

	if (!cmds->args[1])
	{
		//print blabla 
		return ;
	}	
	i = 1;
	while (cmds->args[i])
	{
		var_env.name = get_name(cmds->args[i]);
		if (!var_env.name)
		{
			tools->error_code = 1;
			//print not a valid identifier
			return ;
		}
		var_env.value = get_value(ft_strchr(cmds->args[i], '='));
		printf("IN EXPORT %s\n", var_env.value);
		push_var_to_environ(&var_env);
		free(var_env.name);
		free(var_env.value);
		i++;
	}
}
