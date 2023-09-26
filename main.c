/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:09:31 by adupin            #+#    #+#             */
/*   Updated: 2023/09/26 12:09:39 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "minishell.h"

int	main(void)
{
	char	*line;
	
	line = readline("minishell> ");
	printf("line = %s\n", line);
	return (0);
}
