/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:18:05 by adupin            #+#    #+#             */
/*   Updated: 2023/11/07 10:34:48 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	update_pwd(t_tools *tools, char *new, char *input)
{
	char	*new_m;

	if (!new)
		return ;
	printf("new = %s\n", new);
	if (chdir(new) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	new_m = ft_xstrdup(new);
	free(tools->old_pwd);
	tools->old_pwd = tools->pwd;
	replace_element_to_environ("OLDPWD", tools->old_pwd);
	replace_element_to_environ("PWD", new_m);
	tools->pwd = new_m;
}
// char	*pp_to_str(char **tab, char *c)
// {
// 	char *str;
// 	int	size;
// 	int	i;

// 	i = 0;
// 	size = 0;
// 	while (tab[i])
// 	{
// 		size += ft_strlen(tab[i]) + 1;
// 		i++;
// 	}
// 	str = ft_xmalloc(sizeof(char) * size + 1);
// 	i = 0;
// 	while (tab[i])
// 	{
// 		printf("tab = %s\n",tab[i]);
// 		ft_strlcat(str, tab[i], size + 1);
// 		ft_strlcat(str, c, size + 1);
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// 	str[size - 1] = '\0';
// 	return (str);
// }

// void	remove_back(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		if (!ft_strncmp("..", tab[i], ft_strlen(tab[i])))
// 		{
// 			free(tab[i]);
// 			free(tab[i - 1]);
// 			tab[i - 1] = NULL;
// 			ft_ppcpy(&tab[i - 1], &tab[i + 1]);			
// 		}
// 		else
// 			i++;
// 	}	
// }
// char	*get_absolute_path(char *input, t_tools *tools)
// {
// 	char	*path;
// 	char	**tmp;
// 	char	**s_input;
// 	char	**absolute;

// 	if (input[0] == '~')
// 	{
// 		if (value_var_environ("HOME"))
// 			tmp = ft_split(value_var_environ("HOME"), '/');
// 		else
// 			tmp = ft_xmalloc(sizeof(char));
// 	}
// 	else
// 		tmp = ft_split(tools->pwd, '/');
// 	if (!tmp)
// 		return (NULL);
// 	s_input = ft_split(input, '/');
// 	if (!s_input)
// 		return (NULL);
// 	absolute = ft_xmalloc((ft_pplen(tmp) + ft_pplen(s_input) + 1) * sizeof(char *));
// 	absolute[0] = NULL;
// 	ft_ppcat(absolute, tmp);
// 	ft_ppcat(absolute, s_input);
// 	printf("absolute = %s\n", absolute[0]);
// 	free(tmp);
// 	free(s_input);
// 	remove_back(absolute);
// 	printf("absolute2 = %s\n", absolute[0]);
// 	path = pp_to_str(absolute, "/");
// 	printf("path = %s\n", path);
// 	return (path);
// }

void	ft_cd(t_tools *tools, t_cmds *cmds)
{
	char	*path;
	//CHDIR GERE .. TOUT SEUL ET LES CHEMINS RELATIFS
	
	if (cmds->args[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		return ;
	}
	if (!ft_strncmp(cmds->args[1], "-", ft_strlen(cmds->args[1])))
	{
		if (!value_var_environ("OLDPWD"))
		{
			ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
			return ;
		}
		update_pwd(tools, value_var_environ("OLDPWD"), NULL);
		ft_putendl_fd(tools->pwd, 1);
	}
	else
	{
		path = get_absolute_path(cmds->args[1], tools);
		update_pwd(tools, path, cmds->args[1]);
		free(path);
	}
}
