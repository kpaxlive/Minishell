/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:54:57 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:37:43 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(char *str)
{
	int	counter;
	int	idx;

	counter = 0;
	idx = -1;
	while (str[++idx])
		if (str[idx] == '|' && !in_quotes(str, idx))
			counter++;
	return (counter);
}

int	check_lines(void)
{
	int	idx;

	idx = -1;
	while (g_data.pipesplit[++idx])
	{
		if (!ft_strlen(g_data.pipesplit[idx]))
		{
			print_error("|ragoroliptik|: syntax error", 0);
			g_data.status = 258;
			return (0);
		}
	}
	return (1);
}

char	**manuelsplit(char *str)
{
	int		idx;
	int		len;
	int		x;
	int		count;
	char	**new;

	count = find_arg_count(str);
	new = alloc_mem(count);
	idx = 0;
	x = -1;
	while (--count >= 0)
	{
		while (is_ws(str[idx]))
			idx++;
		if (!str[idx])
			break ;
		len = find_ws_arg(str, idx);
		new[++x] = ft_substr(str, idx, len);
		idx += len + 1;
	}
	return (new);
}

void	fill_pipesplit(char **new, int line)
{
	int		idx;
	char	*tmp;

	idx = -1;
	tmp = ft_strjoin(new[++idx], " ");
	free(g_data.pipesplit[line]);
	g_data.pipesplit[line] = ft_strdup(tmp);
	free(tmp);
	while (new[++idx])
	{
		tmp = ft_strjoin(g_data.pipesplit[line], new[idx]);
		free(g_data.pipesplit[line]);
		g_data.pipesplit[line] = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strjoin(g_data.pipesplit[line], " ");
		free(g_data.pipesplit[line]);
		g_data.pipesplit[line] = ft_strdup(tmp);
		free(tmp);
	}
}

int	get_data(void)
{
	g_data.count_l = count_pipe(g_data.all_line) + 1;
	pipesplit(g_data.all_line);
	if (!check_lines())
		return (1);
	if (!get_redirsep())
		return (2);
	take_args();
	heredoc();
	tripleredir();
	return (0);
}
