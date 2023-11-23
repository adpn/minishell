/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:16:17 by adupin            #+#    #+#             */
/*   Updated: 2023/11/23 14:17:33 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"
#include "struct.h"
#include "utils.h"

typedef struct	s_var_env
{
	char	*name;
	char	*value;
}				t_var_env;

void	builtin(t_tools *tools, t_cmds *cmds);

int		ft_echo(t_cmds *cmd);
int		ft_export(t_cmds *cmds);
int		ft_cd(t_cmds *cmds);
int		ft_pwd(t_cmds *cmds);
int		ft_unset(t_cmds *cmds);
int		ft_env(t_cmds *cmds);
int		ft_exit(t_cmds *cmds);

void	push_var_to_environ(t_var_env *var_env);
#endif