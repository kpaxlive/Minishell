/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:06:54 by dayan             #+#    #+#             */
/*   Updated: 2022/01/21 15:06:56 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*x1;
	const unsigned char	*x2;

	x1 = s1;
	x2 = s2;
	i = 0;
	if (n != 0)
	{
		while (x1[i] == x2[i] && i < n - 1)
			i++;
		return (x1[i] - x2[i]);
	}
	return (0);
}
