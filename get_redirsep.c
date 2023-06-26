/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirsep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:36:13 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:37:54 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_redir(char *str)
{
	int	len;

	len = 0;
	while (str[++len])
		if ((str[len] == '>' || str[len] == '<') && !in_quotes(str, len))
			return (len);
	return (len);
}

int	find_redir_count(char *str)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (str[++i])
	{
		if ((str[i] == '>' || str[i] == '<') && i != 0 && !in_quotes(str, i))
			counter++;
		while (str[i] && (str[i] == '>' || str[i] == '<'))
			i++;
	}
	return (counter + 1);
}

char	**redirsplit(char *str, int idx, int j)
{
	int		counter;
	char	**new;
	char	*tmp;
	int		start;

	counter = find_redir_count(str);
	new = alloc_mem(counter);
	idx = 0;
	start = 0;
	j = -1;
	while (str[idx])
	{
		while (str[idx] == '<' || str[idx] == '>')
			idx++;
		while (str[idx] && ((str[idx] != '<' && str[idx] != '>')
				|| in_quotes(str, idx)))
			idx++;
		new[++j] = ft_substr(str, start, idx - start);
		tmp = ft_strtrim(new[j], " \t\r\v\f\n");
		free(new[j]);
		new[j] = ft_strdup(tmp);
		free(tmp);
		start = idx;
	}
	return (new);
}

int	fix_redirection(int line)
{
	int		redir;
	int		idx;
	char	*holder;

	redir = -1;
	while (g_data.redirsep[line][++redir])
	{
		if (g_data.redirsep[line][redir][0]
			&& g_data.redirsep[line][redir][0] != '<'
			&& g_data.redirsep[line][redir][0] != '>')
			continue ;
		idx = -1;
		while (g_data.redirsep[line][redir][++idx] == '>'
			|| g_data.redirsep[line][redir][idx] == '<')
			;
		if (idx > 2 && g_data.redirsep[line][redir][idx - 1] == '>')
			return (print_error("|ragoroliptik|: syntax error", 0));
		holder = ft_strdup(ft_strchr(g_data.redirsep[line][redir],
					g_data.redirsep[line][redir][idx]));
		if (g_data.redirsep[line][redir][idx]
			&& !is_ws(g_data.redirsep[line][redir][idx]))
			fix_redirection_helper(line, redir, idx, holder);
		free(holder);
	}
	return (1);
}

int	get_redirsep(void)
{
	int	line;
	int	idx;
	int	j;

	g_data.redirsep = malloc(sizeof(char **) * (g_data.count_l + 1));
	g_data.redirsep[g_data.count_l] = 0;
	line = -1;
	idx = 0;
	j = -1;
	while (++line < g_data.count_l)
	{
		g_data.redirsep[line] = redirsplit(g_data.pipesplit[line], idx, j);
		if (!fix_redirection(line))
			return (0);
		if (!redir_sep_helper(line))
			return (0);
		if (!redir_sep_helper_3(line))
			return (0);
		check_commands(line);
		trim_spaces(g_data.redirsep[line]);
	}
	return (1);
}
