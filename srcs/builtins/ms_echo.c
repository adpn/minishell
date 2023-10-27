/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:04:09 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/27 14:19:45 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ms_echo(t_tools *tools, t_cmds *cmd)
{
	int		i;
	int		j;
	bool	trailing;

	(void) tools;
	i = 0;
	if (!ft_strncmp(cmd->args[1], "-n", ft_strlen(cmd->args[1])))
	{
		trailing = false;
		i = 1;
	}
	while (cmd->args[++i])
	{
		j = 0;
		while (cmd->args[i][j])
		{
			if (cmd->args[i][j] == '"')
				continue ;
			write(1, &cmd->args[i][j], 1);
		}
		if (cmd->args[i + 1])
			write(1, " ", 1);
	}
	if (!trailing)
		return ;
	write(1, "\n", 1);
}
