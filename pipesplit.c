/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipesplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:21:21 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:37:57 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_pipe(char *str, int idx)
{
	int	len;	

	len = -1;
	while (str[idx + (++len)])
		if (str[idx + len] == '|' && !in_quotes(str, idx + len))
			return (len);
	return (len);
}

void	fix_redirections(int line)
{
	char	*new;
	int		idx;
	int		j;

	idx = -1;
	j = -1;
	new = malloc(sizeof(char) * (ft_strlen(g_data.pipesplit[line]) + 2));
	while (g_data.pipesplit[line][++idx])
	{
		while (g_data.pipesplit[line][idx] == '<'
		|| g_data.pipesplit[line][idx] == '>')
		{
			new[++j] = g_data.pipesplit[line][idx];
			if (g_data.pipesplit[line][idx + 1] != '<'
				&& g_data.pipesplit[line][idx + 1] != '>'
					&& !in_quotes(g_data.pipesplit[line], idx + 1))
				new[++j] = ' ';
			idx++;
		}
		new[++j] = g_data.pipesplit[line][idx];
	}
	new[++j] = '\0';
	free(g_data.pipesplit[line]);
	g_data.pipesplit[line] = ft_strdup(new);
	free(new);
}

void	pipesplit(char *str)
{
	int		idx;
	int		len;
	int		x;
	char	*tmp;

	g_data.pipesplit = alloc_mem(g_data.count_l);
	idx = 0;
	x = -1;
	while (++x < g_data.count_l)
	{
		len = find_pipe(str, idx);
		g_data.pipesplit[x] = ft_substr(str, idx, len);
		tmp = ft_strtrim(g_data.pipesplit[x], " \t\r\v\f\n");
		free(g_data.pipesplit[x]);
		g_data.pipesplit[x] = ft_strdup(tmp);
		free(tmp);
		idx += len + 1;
	}
}
