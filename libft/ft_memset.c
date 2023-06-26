/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:07:47 by dayan             #+#    #+#             */
/*   Updated: 2022/02/03 17:09:56 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
//harflerini memory üzerinden değiştiriyor
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = s;
	while (i < n)
		p[i++] = (char) c;
	return (p);
}
