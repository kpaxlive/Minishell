/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:39:38 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:38:05 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes(int line, int redir, int arg)
{
	char	*tmp;
	int		idx;
	int		j;

	tmp = malloc(sizeof(char) * (ft_strlen(g_data.args[line][redir][arg]) + 1));
	tmp = fill_tmp(line, redir, arg, tmp);
	free(g_data.args[line][redir][arg]);
	g_data.args[line][redir][arg] = malloc(sizeof(char) * ft_strlen(tmp) + 1);
	idx = -1;
	j = ft_strlen(tmp);
	while (--j >= 0)
		g_data.args[line][redir][arg][++idx] = tmp[j];
	free(tmp);
	g_data.args[line][redir][arg][++idx] = '\0';
}

int	check_in_single_quotes(int idx_sum, int line, int redir, int arg)
{
	int	ret;

	ret = in_quotes(g_data.args[line][redir][arg], idx_sum);
	if (ret == 3)
	{
		while (g_data.args[line][redir][arg][--idx_sum] && idx_sum >= 0)
		{
			if (g_data.args[line][redir][arg][idx_sum] == 39)
				return (2);
			if (g_data.args[line][redir][arg][idx_sum] == '"')
				return (1);
		}
	}
	return (ret);
}

void	replace_variable(int line, int redir, int arg)
{
	char	**old;
	char	*new;
	int		idx;

	old = dollarsplit(g_data.args[line][redir][arg], '$');
	idx = -1;
	new = 0;
	while (old[++idx])
	{
		if (!ft_strchr(old[idx], '$'))
		{
			new = ft_strdup(old[idx]);
			continue ;
		}
		else if (check_in_single_quotes(sum(idx, old), line, redir, arg) == 1)
		{
			new = get_new_2(old[idx], new);
			continue ;
		}
		new = get_new(old[idx], new);
	}
	free_ezhel(old);
	if (new)
		free_new(line, redir, arg, new);
}

void	fill_args(int line, int redir)
{
	int	arg;
	int	idx;
	int	len;

	arg = -1;
	idx = 0;
	while (g_data.redirsep[line][redir][idx])
	{
		while (g_data.redirsep[line][redir][idx]
			&& is_ws(g_data.redirsep[line][redir][idx]))
			idx++;
		if (!g_data.redirsep[line][redir][idx])
			break ;
		len = find_ws_arg(g_data.redirsep[line][redir], idx);
		g_data.args[line][redir][++arg]
			= ft_substr(g_data.redirsep[line][redir], idx, len);
		if (ft_strchr(g_data.args[line][redir][arg], '$'))
			replace_variable(line, redir, arg);
		quotes(line, redir, arg);
		idx += len;
	}
}

void	take_args(void)
{
	int	line;
	int	redir;

	alloc_args();
	line = -1;
	while (++line < g_data.count_l)
	{
		redir = -1;
		while (++redir < redir_count(g_data.pipesplit[line]) + 1)
			fill_args(line, redir);
	}
}
