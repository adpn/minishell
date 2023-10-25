/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:47:46 by alexphil          #+#    #+#             */
/*   Updated: 2023/10/25 14:25:16 by alexphil         ###   ########.fr       */
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
		if (redirects->next)
			printf("\n");
		redirects = redirects->next;
	}
}

void	args_display(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		printf("args[%i]: ", i);
		printf("%s\n", args[i]);
		i++;
	}
}

void	cmds_display(t_cmds *cmds)
{
	int	i;

	i = 1;
	while (cmds)
	{
		printf("COMMAND #%i:\n\n", i++);
		if (cmds->args)
			args_display(cmds->args);
		if (cmds->nb_redirects)
		{
			printf("\nHas %i redirect(s)\n\n", cmds->nb_redirects);
			redirects_display(cmds->redirects);
		}
		cmds = cmds->next;
		printf("\n");
	}
}

void	parser_display(t_tools *tools)
{
	if (!tools->cmds)
	{
		printf("No command found.\n");
		return ;
	}
	printf("\nFound %i command(s)!\n\n", tools->pipes + 1);
	cmds_display(tools->cmds);
}
