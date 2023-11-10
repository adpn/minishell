/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:04:09 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/31 11:18:56 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ms_echo(t_tools *tools, t_cmds *cmd)
{
	int		i;
	int		j;
	int		flag;

	(void) tools;
	i = 0;
	flag = (ft_strncmp(cmd->args[1], "-n", ft_strlen(cmd->args[1])) == 0);
	if (flag)
		i = 1;
	while (cmd->args[++i])
	{
		j = -1;
		while (cmd->args[i][++j])
		{
			if (cmd->args[i][j] == '"')
				continue ;
			write(1, &cmd->args[i][j], 1);
		}
		if (cmd->args[i + 1])
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
}
