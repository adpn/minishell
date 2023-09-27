/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
/*   Updated: 2023/09/27 15:23:43 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
		// printf("line = %s\n", line);
	}
	return (0);
}
