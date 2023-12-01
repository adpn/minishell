/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:10:28 by adupin            #+#    #+#             */
/*   Updated: 2023/12/01 16:13:12 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errors.h"

void	*ft_xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("Error: malloc failed");
		error_mgmt(&g_tools, 0);
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
