/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:08:51 by adupin            #+#    #+#             */
/*   Updated: 2023/11/07 11:13:35 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_pwd(t_tools *tools, t_cmds *cmds)
{
	char	pwd[4096];

	(void)tools;
	(void)cmds;
	getcwd(pwd, 4096);
	printf("%s\n", pwd);
}

void	ft_unset(t_tools *tools, t_cmds *cmds)
{
	extern char **environ;
	int			i;
	int			j;

	(void)tools;
	i = 1;
	while (cmds->args[i])
	{
		j = index_element_environ(cmds->args[i]);
		if (j != -1)
			ft_bzero(environ[j], ft_strlen(environ[j]));
		i++;
	}
}

void	ft_env(t_tools *tools, t_cmds *cmds)
{
	extern char	**environ;
	int	i;
	
	(void)tools;
	(void)cmds;
	if (cmds->args[1])
	{
		printf("env: %s: No such file or directory\n", cmds->args[1]);
		// NEED ERROR CODE
		return ;
	}
	i = 0;
	while (environ[i])
	{
		if(environ[i][0])
			printf("%s\n", environ[i]);
		i++;
	}
}

void	ft_exit(t_tools *tools, t_cmds *cmds)
{
	(void)tools;
	(void)cmds;
	printf("exit\n");
	exit(0);
}

void	builtin(t_tools *tools, t_cmds *cmds)
{
	size_t	len;

	len = ft_strlen(cmds->args[0]);
	if (!ft_strncmp(cmds->args[0], "echo", len))
		ms_echo(tools, cmds);
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
