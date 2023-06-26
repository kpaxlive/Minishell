/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:13:42 by dayan             #+#    #+#             */
/*   Updated: 2022/01/21 15:13:42 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*x;

	x = malloc (nmemb * size);
	if (!x)
		return (0);
	ft_bzero (x, nmemb * size);
	return (x);
}
