/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:16:17 by adupin            #+#    #+#             */
/*   Updated: 2023/12/04 11:47:31 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "struct.h"
# include "utils.h"

void	builtin(t_tools *tools, t_cmds *cmds);

int		ft_echo(t_cmds *cmd);
int		ft_export(t_cmds *cmds);
int		ft_cd(t_cmds *cmds);
int		ft_pwd(t_cmds *cmds);
int		ft_unset(t_cmds *cmds);
int		ft_env(t_cmds *cmds);
int		ft_exit(t_cmds *cmds);

#endif