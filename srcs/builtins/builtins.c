/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:08:51 by adupin            #+#    #+#             */
/*   Updated: 2023/10/25 16:43:43 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_echo(t_tools *tools, t_cmds *cmds)
{
	
}

void	ft_cd(t_tools *tools, t_cmds *cmds)
{

}

void	ft_pwd(t_tools *tools, t_cmds *cmds)
{

}

void	ft_export(t_tools *tools, t_cmds *cmds)
{

}

void	ft_unset(t_tools *tools, t_cmds *cmds)
{
	
}

void	ft_env(t_tools *tools, t_cmds *cmds)
{
	extern char	**environ;
	int	i;
	
	if (cmds->args[1])
	{
		printf("env: %s: No such file or directory\n", cmds->args[1]);
		// NEED ERROR CODE
		return ;
	}
	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

void	ft_exit(t_tools *tools, t_cmds *cmds)
{
	printf("exit\n");
	exit(0);
}

int	builtin(t_tools *tools, t_cmds *cmds)
{
	size_t	len;

	len = ft_strlen(cmds->args[0]);
	if (ft_strncmp(cmds->args[0], "echo", len))
		ft_echo(tools, cmds);
	else if (ft_strncmp(cmds->args[0], "cd", len))
		ft_cd(tools, cmds);
	else if (ft_strncmp(cmds->args[0], "pwd", len))
		ft_pwd(tools, cmds);
	else if (ft_strncmp(cmds->args[0], "export", len))
		ft_export(tools, cmds);
	else if (ft_strncmp(cmds->args[0], "unset", len))
		ft_unset(tools, cmds);
	else if (ft_strncmp(cmds->args[0], "env", len))
		ft_env(tools, cmds);
	else if (ft_strncmp(cmds->args[0], "exit", len))
		ft_exit(tools, cmds);
	else
		return (0);
}
