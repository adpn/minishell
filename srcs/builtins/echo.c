/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:04:09 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/23 13:44:20 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	write_word(t_cmds *cmd, int i)
{
	int			j;
	t_quotes	quotes;

	quotes = (t_quotes){0, 0};
	j = -1;
	while (cmd->args[i][++j])
	{
		update_quotes(&quotes, cmd->args[i][j]);
		if ((cmd->args[i][j] == '\'' && quotes.double_q % 2 == 0)
				|| (cmd->args[i][j] == '\"' && quotes.simple_q % 2 == 0))
			continue ;
		write(1, &cmd->args[i][j], 1);
	}
}

int	ft_echo(t_tools *tools, t_cmds *cmd)
{
	int			i;
	int			flag;

	(void)tools;
	i = 0;
	flag = (ft_strncmp(cmd->args[1], "-n", ft_strlen(cmd->args[1])) == 0);
	if (flag)
		i = 1;
	while (cmd->args[++i])
	{
		write_word(cmd, i);
		if (cmd->args[i + 1])
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
