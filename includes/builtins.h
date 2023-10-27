/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:16:17 by adupin            #+#    #+#             */
/*   Updated: 2023/10/27 14:45:07 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"
#include "struct.h"
#include "utils.h"
# include "struct.h"

void	ms_echo(t_tools *tools, t_cmds *cmd);
void	ft_export(t_tools *tools, t_cmds *cmds);
#endif