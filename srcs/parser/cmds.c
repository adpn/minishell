/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:59:34 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/27 16:39:22 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "struct.h"
#include "parser.h"

void	init_cmd(t_cmds *cmd)
{
	cmd->args = NULL;
	cmd->builtin = NULL;
	cmd->nb_redirects = 0;
	cmd->redirects = NULL;
}

void	add_cmd(t_tools *tools, t_cmds *cmd)
{
	t_cmds	*tmp;

	if (!tools->cmds)
	{
		tools->cmds = cmd;
		cmd->prev = NULL;
	}
	else
	{
		tmp = tools->cmds;
		while (tmp->next)
			tmp = tmp->next;
		cmd->prev = tmp;
		tmp->next = cmd;
	}
	cmd->next = NULL;
}

// Is echo / cd / pwd / export / unset / env / exit ?
void	set_builtin(t_cmds *cmd, char *arg0)
{
	if (!ft_strncmp(arg0, "echo", ft_strlen(arg0)))
		cmd->builtin = ms_echo;
	// else if (!ft_strncmp(arg0, "cd", ft_strlen(arg0)))
	// 	cmd->builtin = ft_cd;
	// else if (!ft_strncmp(arg0, "pwd", ft_strlen(arg0)))
	// 	cmd->builtin = ft_pwd;
	// else if (!ft_strncmp(arg0, "export", ft_strlen(arg0)))
	// 	cmd->builtin = ft_export;
	// else if (!ft_strncmp(arg0, "unset", ft_strlen(arg0)))
	// 	cmd->builtin = ft_unset;
	// else if (!ft_strncmp(arg0, "env", ft_strlen(arg0)))
	// 	cmd->builtin = ft_env;
	// else if (!ft_strncmp(arg0, "exit", ft_strlen(arg0)))
	// 	cmd->builtin = ft_exit;
}

void	new_cmd(t_tools *tools)
{
	t_cmds	*cmd;
	int		nb_args;
	int		i;

	if (tools->lex_list->operator == PIPE)
		tools->lex_list = tools->lex_list->next;
	cmd = ft_xmalloc(sizeof(t_cmds));
	init_cmd(cmd);
	nb_args = count_args(tools->lex_list);
	cmd->args = ft_xmalloc(sizeof(char *) * (nb_args + 1));
	cmd->nb_redirects = count_redirects(tools->lex_list);
	i = 0;
	while (tools->lex_list && tools->lex_list->operator == WORD)
	{
		if (i == 0)
			set_builtin(cmd, tools->lex_list->word);
		cmd->args[i++] = ft_xstrdup(tools->lex_list->word);
		tools->lex_list = tools->lex_list->next;
	}
	cmd->args[i] = NULL;
	while (tools->lex_list && tools->lex_list->operator != PIPE)
		get_redirects(tools, cmd);
	add_cmd(tools, cmd);
}
