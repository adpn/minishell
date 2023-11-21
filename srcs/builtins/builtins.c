/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:08:51 by adupin            #+#    #+#             */
/*   Updated: 2023/11/21 12:53:48 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_pwd(t_tools *tools, t_cmds *cmds)
{
	char	pwd[4096];

	(void)cmds;
	getcwd(pwd, 4096);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	tools->error_code = 0;
}

void	ft_unset(t_tools *tools, t_cmds *cmds)
{
	extern char	**environ;
	int			i;

	i = 1;
	while (cmds->args[i])
	{
		delete_var_environ(cmds->args[i]);
		i++;
	}
	tools->error_code = 0;
}

void	ft_env(t_tools *tools, t_cmds *cmds)
{
	extern char	**environ;
	int			i;

	if (cmds->args[1])
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(cmds->args[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		tools->error_code = 127; //127 normalement
		return ;
	}
	i = 0;
	while (environ[i])
	{
		ft_putendl_fd(environ[i], STDOUT_FILENO);
		i++;
	}
	tools->error_code = 0;
}

void	ft_exit(t_tools *tools, t_cmds *cmds)
{
	(void)tools;
	(void)cmds;
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(0);
}

void	builtin(t_tools *tools, t_cmds *cmds)
{
	size_t	len;

	len = ft_strlen(cmds->args[0]);
	if (!ft_strncmp(cmds->args[0], "echo", len))
		ft_echo(tools, cmds);
	else if (!ft_strncmp(cmds->args[0], "cd", len))
		ft_cd(tools, cmds);
	else if (!ft_strncmp(cmds->args[0], "pwd", len))
		ft_pwd(tools, cmds);
	else if (!ft_strncmp(cmds->args[0], "export", len))
		ft_export(tools, cmds);
	else if (!ft_strncmp(cmds->args[0], "unset", len))
		ft_unset(tools, cmds);
	else if (!ft_strncmp(cmds->args[0], "env", len))
		ft_env(tools, cmds);
	else if (!ft_strncmp(cmds->args[0], "exit", len))
		ft_exit(tools, cmds);
}
