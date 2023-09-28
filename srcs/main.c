/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
/*   Updated: 2023/09/28 14:20:56 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_lex	*lex;

	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
		lex = lexer(line);
		if (!lex)
			return (1);
		print_lex(lex);
		free_lex(lex);
		free(line);
		// printf("line = %s\n", line);
	}
	return (0);
}
