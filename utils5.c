/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:53:30 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 16:53:31 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_tmp(int line, int redir, int arg, char *tmp)
{
	int	ret;
	int	idx;
	int	j;

	idx = ft_strlen(g_data.args[line][redir][arg]);
	j = -1;
	while (g_data.args[line][redir][arg][--idx] && idx >= 0)
	{
		if (g_data.args[line][redir][arg][idx] == '"'
			|| g_data.args[line][redir][arg][idx] == 39)
		{
			ret = in_quotes(g_data.args[line][redir][arg], idx);
			if ((g_data.args[line][redir][arg][idx] == '"'
				&& ret != 1 && ret != 3)
				|| (g_data.args[line][redir][arg][idx] == 39
					&& ret != 2 && ret != 3))
				continue ;
		}
		tmp[++j] = g_data.args[line][redir][arg][idx];
	}
	tmp[++j] = '\0';
	return (tmp);
}

char	*get_value(char *key)
{
	char	*value;
	int		key_idx;

	key_idx = in_env(key) - 1;
	if (in_env(key))
		value = ft_strdup(ft_strchr(g_data.env[key_idx], '=') + 1);
	else if (!ft_strcmp(key, "?"))
		value = ft_itoa(g_data.status);
	else
		value = ft_strdup("");
	return (value);
}

char	*get_new(char *old_str, char *new)
{
	char	*tmp;
	char	*key;
	char	*value;

	key = ft_substr(old_str, 1, find_key_size(old_str + 1));
	value = get_value(key);
	if (!new)
		new = ft_strjoin(value, ft_strnstr(old_str, key,
					ft_strlen(key) + 1) + ft_strlen(key));
	else
	{
		tmp = ft_strdup(new);
		free(new);
		new = ft_strjoin(tmp, value);
		free(tmp);
		tmp = ft_strdup(new);
		free(new);
		new = ft_strjoin(tmp, ft_strnstr(old_str, key,
					ft_strlen(key) + 1) + ft_strlen(key));
		free(tmp);
	}
	free(value);
	free(key);
	return (new);
}

char	*get_new_2(char *old_str, char *new)
{
	char	*tmp;

	if (new)
	{
		tmp = ft_strdup(new);
		free(new);
		new = ft_strjoin(tmp, old_str);
		free(tmp);
	}
	else
		new = ft_strdup(old_str);
	return (new);
}

void	free_new(int line, int redir, int arg, char *new)
{
	free(g_data.args[line][redir][arg]);
	g_data.args[line][redir][arg] = ft_strdup(new);
	free(new);
}
