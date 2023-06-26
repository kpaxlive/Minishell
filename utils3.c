/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:19:24 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:38:14 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_char(char *str, char x)
{
	int	idx;
	int	counter;

	idx = -1;
	counter = 0;
	while (str[++idx])
		if (str[idx] == x)
			counter++;
	return (counter);
}

int	find_size(char *str, char c)
{
	int	size;

	size = 0;
	while (str[++size])
		if (str[size] == c)
			return (size);
	return (size);
}

char	**dollarsplit(char *str, char x)
{
	char	**new;
	char	*tmp;
	int		idx;
	int		size;
	int		j;

	if (str[0] == '$')
		idx = 0;
	else if (str[0] != '$' && (is_ws(str[0] || str[0] == 39 || str[0] == '"')))
		idx = 0;
	else
		idx = 1;
	new = alloc_mem(count_char(str, x) + idx);
	idx = 0;
	j = -1;
	while (str[idx])
	{
		size = find_size(str + idx, x);
		tmp = ft_substr(str, idx, size);
		new[++j] = ft_strdup(tmp);
		free(tmp);
		idx += size;
	}
	return (new);
}

int	find_key_size(char *str)
{
	int	idx;

	idx = -1;
	while (str[++idx])
		if (is_ws(str[idx]) || str[idx] == 39 || str[idx] == '"')
			return (idx);
	return (idx);
}

int	is_ws(char c)
{
	if (c == ' ')
		return (32);
	else if (c == '\t')
		return (9);
	else if (c == '\n')
		return (10);
	else if (c == '\v')
		return (11);
	else if (c == '\f')
		return (12);
	else if (c == '\r')
		return (13);
	return (0);
}
