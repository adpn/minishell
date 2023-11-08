/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:47:36 by adupin            #+#    #+#             */
/*   Updated: 2023/11/08 10:48:33 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool is_inside_quotes(t_quotes *quotes)
{
	if (quotes->double_q % 2 == 1 || quotes->simple_q % 2 == 1)
		return (true);
	return (false);
}
void	update_quotes(t_quotes *quotes, char c)
{
	if (c == '\'' && !(quotes->double_q % 2))
		quotes->simple_q++;
	else if (c == '\"' && !(quotes->simple_q % 2))
		quotes->double_q++;
}