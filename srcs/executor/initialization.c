/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:15:16 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/28 10:16:52 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	init_executor(t_tools *tools)
{
	tools->in_cmd = 1;
	if (tools->pipes == 0)
		single_cmd(tools, tools->cmds);
	else
	{
		tools->pid = ft_calloc(sizeof(int), tools->pipes + 2);
		if (!tools->pid)
			error_mgmt(tools, 0);
		executor(tools);
	}
	tools->in_cmd = 0;
}
