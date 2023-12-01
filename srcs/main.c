/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
/*   Updated: 2023/12/01 16:05:39 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "lexer.h"
#include "parser.h"
#include "builtins.h"
#include "expander.h"
#include "executor.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	handle_sigint(int sig)
{
	g_tools.sig_called = 130;
	if (!g_tools.in_heredoc)
		ft_putchar_fd('\n', STDOUT_FILENO); // ERR or OUT ?
	if (g_tools.in_cmd)
	{
		g_tools.stop_heredoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	else
	{
		rl_replace_line("", 0);
		// ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	g_tools.error_code = 130;
	(void) sig;
}

void	handle_sigquit(int sig)
{
	g_tools.sig_called = 131;
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv)
{
	char	*line;

	if (argc != 1)
		return (1);
	(void)argv;
	init_environ();
	initools(&g_tools); // Where is init supposed to go ?
	g_tools.error_code = 0;
	while (1)
	{
		line = readline("TerminalCancer> ");
		g_tools.sig_called = 0;
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
			// print_lex(g_tools.lex_list);
			if (g_tools.lex_list)
			{
				parser(&g_tools);
				// expand(g_tools.cmds->args, &g_tools);
				init_executor(&g_tools);
				// executor(&g_tools);
				// builtin(&g_tools, g_tools.cmds);
				resetools(&g_tools);
				//free_lex_chained(g_tools.lex_list);
				// exit(0);
			}
		}
		free(line);
	}
	return (0);
}
