/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:37:30 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:37:34 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *str, char *variable)
{
	int	i;

	i = -1;
	if (str)
		while (str[++i])
			write(2, &str[i], 1);
	i = -1;
	if (variable)
		while (variable[++i])
			write(2, &variable[i], 1);
	write(2, &"\n", 1);
	return (0);
}

void	check_files(int line)
{
	int	redir;

	redir = 0;
	while (g_data.args[line][++redir])
	{
		if (!g_data.args[line][redir][1])
		{
			print_error("|ragoroliptik|: syntax error", 0);
			exit(1);
		}
	}
}

int	return_ret(void)
{
	char	**tmp;
	int		ret;
	int		oldpwd_idx;

	oldpwd_idx = in_env("OLDPWD") - 1;
	tmp = ft_split(g_data.env[oldpwd_idx], '=');
	ret = chdir(tmp[1]);
	free_ezhel(tmp);
	return (ret);
}

char	**new_env_function(char **new_env, int layer, int idx)
{
	char	**line;
	int		j;
	int		i;

	j = -1;
	i = -1;
	while (g_data.env[++j])
	{
		line = ft_split(g_data.env[j], '=');
		if (!ft_strcmp(g_data.args[layer][0][idx], line[0]))
			j++;
		if (!g_data.env[j])
		{
			free_ezhel(line);
			break ;
		}
		new_env[++i] = ft_strdup(g_data.env[j]);
		free_ezhel(line);
	}
	new_env[++i] = 0;
	return (new_env);
}

int	find_ws_arg(char *str, int idx)
{
	int	len;

	len = 0;
	while (str[idx + len])
	{
		if ((is_ws(str[idx + len]) && !in_quotes(str, idx + len))
			|| !str[idx + len])
			return (len);
		len++;
	}
	return (len);
}
