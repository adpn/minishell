/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:20:29 by adupin            #+#    #+#             */
/*   Updated: 2023/11/09 11:21:00 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	ft_in_charset(char c, char *charset)
{
	int	i;
	
	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (true);
		i++;
	}
	return (false);
}
