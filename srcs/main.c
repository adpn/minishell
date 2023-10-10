/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/03 11:43:09 by alexphil         ###   ########.fr       */
=======
/*   Updated: 2023/10/09 12:33:28 by adupin           ###   ########.fr       */
>>>>>>> 5f0c04bba1b8c77c76f177cb96e89a7a192d86fc
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
<<<<<<< HEAD
	t_lex	*lex;

	(void)av;
	// structure.envp = envp;
	if (ac != 1)
		return (1);
=======
	//t_lex	*lex;
	char 	*expanded;
>>>>>>> 5f0c04bba1b8c77c76f177cb96e89a7a192d86fc
	while (1)
	{
		line = readline("TerminalCancer> ");
		printf("||%s||\n", line);
		if (line[0])
		{
			add_history(line);
			expanded = complete_string(line);
			if (!expanded)
				return (1);
			printf("expanded %s\n", expanded);
			//free(expanded);
			// lex = lexer(line);
			// if (lex)
			// {
			// print_lex(lex);
			// free_lex_chained(lex);
			// }
		}
		//free(line);
		// printf("line = %s\n", line);
	}
	return (0);
}
