/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:12:33 by dayan             #+#    #+#             */
/*   Updated: 2022/02/03 17:14:28 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"
//int i ve int length size_t idi
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;
	int		lenght;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	lenght = 0;
	if (len > ft_strlen(s) - start)
		lenght = (ft_strlen(s) - start);
	else if (len <= ft_strlen(s) - start)
		lenght = len;
	sub = (char *) malloc ((lenght + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (s[i] && i < lenght)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
