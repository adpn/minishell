/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:16:57 by adupin            #+#    #+#             */
/*   Updated: 2023/11/17 14:35:46 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	index_min_value(char **tab, int len) 
{
	int		i;
	char	*min_value;
	int		min_index;

	i = 0;
	min_value = NULL;
	min_index = -1;
	while (i < len)
	{
		if (!min_value && tab[i])
		{
			min_value = tab[i];
			min_index = i;
		}
		else if (tab[i] && tab[min_index] && ft_strncmp(tab[min_index], tab[i], ft_strlen(tab[min_index])) > 0)
			min_index = i;
		i++;
	}
	return(min_index);	
}

void	print_in_alphabet_order(void)
{
	int			min_index;
	extern char	**environ;
	char		**cpy_environ;
	int			len;

	cpy_environ = array_copy(environ);
	len = ft_array_len(cpy_environ);
	while (1)
	{
		min_index = index_min_value(cpy_environ, len);
		if (min_index != -1 && cpy_environ[min_index])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putendl_fd(cpy_environ[min_index], 1);
			free(cpy_environ[min_index]);
			cpy_environ[min_index] = NULL;
		}
		else
			break ;
	}
	free(cpy_environ);
}

void	push_var_to_environ(t_var_env *var_env)
{
	char	*value;

	value = var_env->value;
	if (!value)
	{
		free(var_env->name);
		return ;
	}
	if (index_element_environ(var_env->name) == -1)
		add_element_to_environ(var_env->name, value);
	else
		replace_element_to_environ(var_env->name, value);
	free(var_env->name);
	free(var_env->value);
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
	if (ft_isdigit(name[0]) || !name[0])
		return (free(name), NULL);
	return (name);
}

void	ft_export(t_tools *tools, t_cmds *cmds)
{
	t_var_env	var_env;
	int		i;

	if (!cmds->args[1])
	{
		print_in_alphabet_order();
		return ;
	}
	i = 1;
	while (cmds->args[i])
	{
		var_env.name = get_name(cmds->args[i]);
		if (!var_env.name)
		{
			tools->error_code = 1;
			ft_print_error("export: `",
				cmds->args[i], "': not a valid identifier\n");
			return ;
		}
		var_env.value = get_value(ft_strchr(cmds->args[i], '='));
		push_var_to_environ(&var_env);
		i++;
	}
}
