/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:15:16 by alexphil          #+#    #+#             */
/*   Updated: 2023/12/01 16:28:30 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	init_executor(t_tools *tools)
{
	if (!tools->cmds)
		return ;
	signal(SIGQUIT, handle_sigquit);
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
