/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:50:38 by alexphil          #+#    #+#             */
/*   Updated: 2023/11/21 09:56:52 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int	cmd_not_found(char *nope)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(nope, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}
