/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:50:38 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/24 16:33:59 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int	parser_token_error(t_tools *tools, int operator)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (operator == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else if (operator == HEREDOC)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (operator == R_APP)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (operator == R_INPUT)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (operator == R_OUTPUT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	resetools(tools);
	return (EXIT_FAILURE);
}

void	error_mgmt(t_tools *tools, int code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (code == 0)
		ft_putstr_fd("failure to allocate memory\n", STDERR_FILENO);
	if (code == 1)
		ft_putstr_fd("failure to create pipe\n", STDERR_FILENO);
	if (code == 2)
		ft_putstr_fd("failure to fork process\n", STDERR_FILENO);
	resetools(tools);
}
