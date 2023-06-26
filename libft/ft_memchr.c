/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:06:44 by dayan             #+#    #+#             */
/*   Updated: 2022/01/21 15:06:45 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char				*p;
	size_t				i;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (char)c)
			return ((void *)(p + i));
		i++;
	}
	return (0);
}
