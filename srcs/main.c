/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
/*   Updated: 2023/10/03 10:00:51 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_lex	*lex;

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
