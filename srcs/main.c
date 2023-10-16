/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
/*   Updated: 2023/10/16 11:32:28 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_line;

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_line = NULL;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		//rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_redisplay();
		
	}

}

int	main(void)
{
	//char	*line;
	t_lex	*lex;
	// struct sigaction sig;
	
	// char 	*expanded;
	
	// sig.sa_sigaction = signal_handler;
	// sig.sa_flags = SA_SIGINFO;
	// sigaction(SIGINT, &sig, NULL);
	// sigaction(SIGQUIT, &sig, NULL);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		g_line = readline("TerminalCancer> ");
		if (!g_line)
		{
			printf("exit\n");
			return (0);
		}
		if (g_line && g_line[0])
		{
			add_history(g_line);
			// expanded = complete_string(line);
			// if (!expanded)
			// 	return (1);
			// printf("expanded %s\n", expanded);
			//free(expanded);
			lex = lexer(g_line);
			if (lex)
			{
			print_lex(lex);
			free_lex_chained(lex);
			}
		}
		
		//free(line);
		// printf("line = %s\n", line);
	}
	return (0);
}
