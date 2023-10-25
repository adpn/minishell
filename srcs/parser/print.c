/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:47:46 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/24 14:06:53 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "struct.h"

void	redirects_display(t_lex	*redirects)
{
	int	i;

	i = 1;
	while (redirects)
	{
		printf("Redirect #%i:\n", i++);
		printf("Type: ");
		if (redirects->operator == R_APP)
			printf("APPEND\n");
		else if (redirects->operator == R_INPUT)
			printf("INPUT\n");
		else if (redirects->operator == R_OUTPUT)
			printf("OUTPUT\n");
		printf("File: %s\n", redirects->word);
		redirects = redirects->next;
	}
}

void	args_display(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		printf("args[%i]\t", i);
		printf("%s\n", args[i]);
		i++;
	}
}

void	cmds_display(t_cmds *cmds)
{
	printf("Command:\n");
	if (cmds->args)
		args_display(cmds->args);
	if (cmds->nb_redirects)
	{
		printf("Found %i redirect(s):\n", cmds->nb_redirects);
		redirects_display(cmds->redirects);
	}
}

void	parser_display(t_tools *tools)
{
	if (!tools->cmds)
	{
		printf("No command found.\n");
		return ;
	}
	printf("Found %i commands!\n", tools->pipes + 1);
	cmds_display(tools->cmds);
}
