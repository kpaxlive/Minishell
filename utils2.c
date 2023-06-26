/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:23:28 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:38:12 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_arg_count(char *str)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (str[++i])
	{
		if (is_ws(str[i]) && !in_quotes(str, i))
			counter++;
		while (str[i] && is_ws(str[i]))
			i++;
	}
	return (counter + 1);
}

void	free_ezhel(char **str)
{
	int	x;

	x = -1;
	while (str[++x])
		free(str[x]);
	free(str);
}

void	free_data(void)
{
	int	line;
	int	redir;

	line = -1;
	while (g_data.args[++line])
	{
		free_ezhel(g_data.redirsep[line]);
		redir = -1;
		while (g_data.args[line][++redir])
			free_ezhel(g_data.args[line][redir]);
		free(g_data.args[line]);
	}
	free(g_data.args);
	free(g_data.redirsep);
	if (g_data.path)
		free_ezhel(g_data.path);
	free_ezhel(g_data.pipesplit);
	free(g_data.all_line);
	line = -1;
	while (++line < g_data.count_l)
		free(g_data.pipes[line]);
	free(g_data.pipes);
	g_data.status /= 256;
}

int	in_env(char	*str)
{
	int		i;
	char	**line;

	i = -1;
	while (g_data.env[++i])
	{
		line = ft_split(g_data.env[i], '=');
		if (!ft_strcmp(line[0], str))
		{
			free_ezhel(line);
			return (i + 1);
		}
		free_ezhel(line);
	}
	return (0);
}

int	ft_setenv(char *key, char *value)
{
	int		idx;
	char	*new;
	char	*new_value;

	if (value)
		new_value = ft_strdup(value);
	else
		new_value = ft_strdup("");
	idx = in_env(key);
	if (idx--)
	{
		free(g_data.env[idx]);
		new = ft_strjoin(key, "=");
		g_data.env[idx] = ft_strjoin(new, new_value);
		free(new);
		free(new_value);
		return (1);
	}
	free(new_value);
	return (0);
}
