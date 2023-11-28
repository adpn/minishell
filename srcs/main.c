/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
/*   Updated: 2023/11/28 10:23:09 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "lexer.h"
#include "parser.h"
#include "builtins.h"
#include "expander.h"
#include "executor.h"

#define CLEAR_FROM_CURSOR	"\033[0K"

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_tools.error_code = 130;
	}
	if (sig == SIGQUIT)
	{
		rl_redisplay();
		ft_putstr_fd(CLEAR_FROM_CURSOR, STDOUT_FILENO);
	}
}

int	main(int argc, char **argv)
{
	char	*line;

	if (argc != 1)
		return (1);
	(void)argv;
	init_environ();
	initools(&g_tools); // Where is init supposed to go ?
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	g_tools.error_code = 0;
	while (1)
	{
		line = readline("TerminalCancer> ");
		if (!line)
		{
			//free_environ();
			ft_putendl_fd("exit", STDOUT_FILENO);
			return (0);
		}
		if (line && line[0])
		{
			add_history(line);
			g_tools.lex_list = lexer(line);
			if (g_tools.lex_list)
			{
				parser(&g_tools);
				// expand(g_tools.cmds->args, &g_tools);
				init_executor(&g_tools);
				// executor(&g_tools);
				// builtin(&g_tools, g_tools.cmds);
				free_lex_chained(g_tools.lex_list);
				// exit(0);
			}
		}
		free(line);
	}
	return (0);
}
