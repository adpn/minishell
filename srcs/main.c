/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
/*   Updated: 2023/12/04 14:21:04 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "lexer.h"
#include "parser.h"
#include "builtins.h"
#include "expander.h"
#include "executor.h"

void	handle_sigint(int sig)
{
	g_tools.sig_called = 130;
	if (!g_tools.in_heredoc)
		ft_putchar_fd('\n', STDERR_FILENO);
	if (g_tools.in_cmd)
	{
		g_tools.stop_heredoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	else
	{
		rl_replace_line("", 0);
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
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	miniloop(t_tools *tools)
{
	char	*line; 

	while (1)
	{
		line = readline("TerminalCancer> ");
		tools->sig_called = 0;
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			return (0);
		}
		if (line && line[0])
		{
			add_history(line);
			tools->lex_list = lexer(line);
			if (tools->lex_list)
			{
				parser(tools);
				init_executor(tools);
				resetools(tools);
			}
		}
		free(line);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 1)
		return (1);
	(void)argv;
	init_environ();
	initools(&g_tools);
	g_tools.error_code = 0;
	return (miniloop(&g_tools));
}
