/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
/*   Updated: 2023/10/11 10:48:25 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_lex	*lex;
	// char 	*expanded;
	
	while (1)
	{
		line = readline("TerminalCancer> ");
		printf("||%s||\n", line);
		if (line[0])
		{
			add_history(line);
			// expanded = complete_string(line);
			// if (!expanded)
			// 	return (1);
			// printf("expanded %s\n", expanded);
			//free(expanded);
			lex = lexer(line);
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
