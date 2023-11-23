/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:18:05 by adupin            #+#    #+#             */
/*   Updated: 2023/11/23 14:16:54 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	error_cd(char *home, char *new, char *pwd, int move)
{
	if (!home && move == 1)
		ft_print_error("cd", ": HOME not set", "\n");
	else
	{
		ft_print_error("cd: ", "", "");
		if (move == 1)
			ft_putstr_fd(home, 2);
		ft_putstr_fd(new + move, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (move == 1)
		chdir(pwd);
}

int	update_pwd(char *new)
{
	char	*home;
	char	pwd[4096];

	getcwd(pwd, 4096);
	home = value_var_environ("HOME");
	if (!new || !ft_strncmp("~/", new, 2)
		|| !ft_strncmp("~", new, ft_strlen(new)))
	{
		if ((chdir(home) == -1)
			|| (new && new[1] && new[2] && chdir(new + 2) == -1))
		{
			error_cd(home, new, pwd, 1);
			return (1);
		}
	}
	else if (chdir(new) == -1)
	{
		error_cd(home, new, pwd, 0);
		return (1);
	}
	replace_element_to_environ("OLDPWD", pwd);
	getcwd(pwd, 4096);
	replace_element_to_environ("PWD", pwd);
	return (0);
}

int	ft_cd(t_cmds *cmds)
{
	char	*old;

	if (cmds->args[1] && cmds->args[2])
	{
		ft_print_error("cd: ", "too many arguments", "\n");
		return (1);
	}
	if (cmds->args[1] && cmds->args[1][0] == '-' && !cmds->args[1][1])
	{
		old = value_var_environ("OLDPWD");
		if (!old)
		{
			ft_print_error("cd: ", "OLDPWD not set", "\n");
			return (1);
		}
		ft_putendl_fd(old, 1);
		return (update_pwd(old));
	}
	else
		return (update_pwd(cmds->args[1]));
}
