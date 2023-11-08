/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:18:05 by adupin            #+#    #+#             */
/*   Updated: 2023/11/08 14:17:48 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	error_cd(char *home, char *new, char *pwd, int move)
{
	if (!home &&  move == 1)
		ft_putendl_fd("bash: cd: HOME not set", 2);
	else
	{
		ft_putstr_fd("bash: cd: ", 2);
		if (move == 1)
			ft_putstr_fd(home, 2);
		ft_putstr_fd(new + move, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (move == 1)
		chdir(pwd);
}

void	update_pwd(t_tools *tools, char *new)
{
	char	*home;
	char	pwd[4096];

	getcwd(pwd, 4096);
	(void)tools;
	home = value_var_environ("HOME");
	if (!new || !ft_strncmp("~/", new, 2) || !ft_strncmp("~", new, ft_strlen(new)))
	{
		if (chdir(home) == -1)
		{
			error_cd(home, new, pwd, 1);
			return ;
		}
		if (new && new[1] && new[2] && chdir(new + 2) == -1)
		{
			error_cd(home, new, pwd, 1);
			return ;
		}
	}
	else if (chdir(new) == -1)
	{
		error_cd(home, new, pwd, 0);
		return ;
	}
	replace_element_to_environ("OLDPWD", pwd); //maybe remove the create if not exist, need to check in bash
	getcwd(pwd, 4096);
	replace_element_to_environ("PWD", pwd); //same than above
}

void	ft_cd(t_tools *tools, t_cmds *cmds)
{
	char	*old;
	//CHDIR GERE .. TOUT SEUL ET LES CHEMINS RELATIFS
	
	if (cmds->args[1] && cmds->args[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		return ;
	}
	if (cmds->args[1] && !ft_strncmp(cmds->args[1], "-", ft_strlen(cmds->args[1])))
	{
		old = value_var_environ("OLDPWD");
		if (!old)
		{
			ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
			return ;
		}
		update_pwd(tools, old);
		ft_putendl_fd(old, 1);
	}
	else
	{
		update_pwd(tools, cmds->args[1]);
	}
}
