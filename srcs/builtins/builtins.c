/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:08:51 by adupin            #+#    #+#             */
/*   Updated: 2023/11/23 15:04:39 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_cmds *cmds)
{
	char	pwd[4096];

	(void)cmds;
	getcwd(pwd, 4096);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (0);
}

int	ft_unset(t_cmds *cmds)
{
	extern char	**environ;
	int			i;

	i = 1;
	while (cmds->args[i])
	{
		delete_var_environ(cmds->args[i]);
		i++;
	}
	return (0);
}

int	ft_env(t_cmds *cmds)
{
	extern char	**environ;
	int			i;

	if (cmds->args[1])
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(cmds->args[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (127);
	}
	i = 0;
	while (environ[i])
	{
		ft_putendl_fd(environ[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

int	ft_exit(t_cmds *cmds)
{
	(void)cmds;
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(0);
}

void	builtin(t_tools *tools, t_cmds *cmds)
{
	size_t	len;

	(void)tools;
	len = ft_strlen(cmds->args[0]);
	if (!ft_strncmp(cmds->args[0], "echo", len))
		ft_echo(cmds);
	else if (!ft_strncmp(cmds->args[0], "cd", len))
		ft_cd(cmds);
	else if (!ft_strncmp(cmds->args[0], "pwd", len))
		ft_pwd(cmds);
	else if (!ft_strncmp(cmds->args[0], "export", len))
		ft_export(cmds);
	else if (!ft_strncmp(cmds->args[0], "unset", len))
		ft_unset(cmds);
	else if (!ft_strncmp(cmds->args[0], "env", len))
		ft_env(cmds);
	else if (!ft_strncmp(cmds->args[0], "exit", len))
		ft_exit(cmds);
}
