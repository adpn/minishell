/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
/*   Updated: 2023/10/25 14:45:41 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "lexer.h"
#include "parser.h"

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		//g_line = NULL;
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	//t_tools	tools;

	if (argc != 1)
		return (1);
	(void)argv;
	g_tools.envp = envp;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		line = readline("TerminalCancer> ");
		if (!line)
		{
			printf("exit\n");
			return (0);
		}
		if (line && line[0])
		{
			add_history(line);
			g_tools.lex_list = lexer(line);
			if (g_tools.lex_list)
			{
				print_lex(g_tools.lex_list);
				// free_lex_chained(tools.lex_list);
			}
			parser(&g_tools);
		}
		free(line);
		
		// free(line);
		// printf("line = %s\n", line);
	}
	return (0);
}
