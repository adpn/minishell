/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
/*   Updated: 2023/10/27 16:39:35 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "lexer.h"
#include "parser.h"
#include "builtins.h"

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
				// print_lex(tools.lex_list);
				parser(&g_tools);
				builtin(&g_tools, g_tools.cmds);
				free_lex_chained(g_tools.lex_list);
			}
		}
		free(line);
		// free(line);
		// printf("line = %s\n", line);
	}
	return (0);
}

// // MAIN FOR PARSER DEBUGING
// void	add_lex(t_tools *tools, char *word, int operator)
// {
// 	t_lex	*node;
// 	t_lex	*tmp;

// 	node = malloc(sizeof(t_lex));
// 	node->word = word;
// 	node->operator = operator;
// 	if (!tools->lex_list)
// 	{
// 		tools->lex_list = node;
// 		node->prev = NULL;
// 	}
// 	else
// 	{
// 		tmp = tools->lex_list;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		node->prev = tmp;
// 		tmp->next = node;
// 	}
// 	node->next = NULL;
// }

// // cat < Makefile | grep "DIR" > res.txt
// void	fake_lex(t_tools *tools)
// {
// 	tools->lex_list = NULL;
// 	add_lex(tools, "cat", WORD);
// 	add_lex(tools, NULL, R_INPUT);
// 	add_lex(tools, "Makefile", WORD);
// 	add_lex(tools, NULL, PIPE);
// 	add_lex(tools, "grep", WORD);
// 	add_lex(tools, "DIR", WORD);
// 	add_lex(tools, NULL, R_OUTPUT);
// 	add_lex(tools, "res.txt", WORD);
// }

// int	main(void)
// {
// 	t_tools	tools;

// 	fake_lex(&tools);
// 	print_lex(tools.lex_list);
// 	parser(&tools);
// 	printf("===================\n");
// 	print_lex(tools.lex_list);
// 	printf("===================\n");
// }
