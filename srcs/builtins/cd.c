/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:18:05 by adupin            #+#    #+#             */
/*   Updated: 2023/11/02 14:10:02 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*home_path(char *path)
{
	char	*home;
	char	*new;

	home = value_var_environ("HOME");
	if (!home)
	{
		if (!path[0])
			return (NULL);
		return (ft_xstrdup(path));
	}
	if (!path || !path[0])
		return (ft_xstrdup(path));
	new = ft_strjoin(home, path);
	if (!new)
		return (NULL);
	return (new);
}

void	update_pwd(t_tools *tools, char *new)
{
	char	*new_m;

	if (!new)
		return ;
	new_m = ft_xstrdup(new);
	if (chdir(new_m) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(new_m, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	free(tools->old_pwd);
	tools->old_pwd = tools->pwd;
	replace_element_to_environ("OLDPWD", tools->old_pwd);
	replace_element_to_environ("PWD", new_m);
	tools->pwd = new_m;
}

char	*get_absolute_path(t_tools *tools, char *str)
{
	char	*path;
	char	*new;
	int		i;
	int		j;

	path = ft_xmalloc(ft_strlen(str) * sizeof(char) + 2);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '\"' && str[i] != '\'')
			path[j++] = str[i];
		i++;
	}
	path[j] = '\0';
	if (path[0] == '~') 
	{
		new = home_path(path + 1);
		free(path);
		return (new);
	}
	new = ft_strjoin(tools->pwd, path);
	free(path);
	return(new);
}

void	ft_cd(t_tools *tools, t_cmds *cmds)
{
	char	*path;
	
	if (!cmds->args[1])
	{
		update_pwd(tools, get_absolute_path(tools, "~"));
		return ;
	}
	if (cmds->args[2])
	{
		ft_putendl_fd("bash: cd: too many arguments", 2);
		return ;
	}
	path = get_absolute_path(tools, cmds->args[1]);
	update_pwd(tools, path);
	free(path);
	//Need to update PWD and OLD, in environ and in struct
}
