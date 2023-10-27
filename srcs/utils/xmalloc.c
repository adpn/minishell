/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:10:28 by adupin            #+#    #+#             */
/*   Updated: 2023/10/26 12:55:25 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	*ft_xcalloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_xmalloc(count * size);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_xstrdup(const char *s1)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s1) + 1;
	dup = ft_xmalloc(len);
	ft_strlcpy(dup, s1, len);
	return (dup);
}
