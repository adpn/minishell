/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
/*   Updated: 2023/10/03 11:43:09 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_lex	*lex;

	(void)av;
	// structure.envp = envp;
	if (ac != 1)
		return (1);
	while (1)
	{
		line = readline("TerminalCancer> ");
		printf("||%s||\n", line);
		if (line[0])
		{
			add_history(line);
			lex = lexer(line);
			if (lex)
			{
			print_lex(lex);
			free_lex_chained(lex);
			}
		}
		free(line);
		// printf("line = %s\n", line);
	}
	return (0);
}
