/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:23:28 by dayan             #+#    #+#             */
/*   Updated: 2022/11/30 16:23:29 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_export_function(char **new_env, int layer, int idx)
{
	char	**line;
	int		j;
	int		i;

	j = -1;
	i = -1;
	while (g_data.export[++j])
	{
		line = ft_split(g_data.export[j], '=');
		if (!ft_strcmp(g_data.args[layer][0][idx], line[0]))
			j++;
		if (!g_data.export[j])
		{
			free_ezhel(line);
			break ;
		}
		new_env[++i] = ft_strdup(g_data.export[j]);
		free_ezhel(line);
	}
	new_env[++i] = 0;
	return (new_env);
}

int	isthere_ws(char *str)
{
	int	idx;

	idx = -1;
	while (str[++idx])
		if (is_ws(str[idx]))
			return (1);
	return (0);
}

void	remove_key_export(int idx, int arg_count, int i, int layer)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * arg_count);
	if (!new_env)
		return ;
	new_env = new_export_function(new_env, layer, idx);
	free_ezhel(g_data.export);
	arg_count = count_arg(new_env);
	g_data.export = malloc(sizeof(char *) * (arg_count + 1));
	g_data.export[arg_count] = 0;
	i = -1;
	while (new_env[++i])
		g_data.export[i] = ft_strdup(new_env[i]);
	free_ezhel(new_env);
}

int	is_numeric(char *str)
{
	int	idx;

	idx = -1;
	while (str[++idx])
		if ((str[idx] >= 33 && str[idx] <= 47)
			|| (str[idx] >= 58 && str[idx] <= 126))
			return (0);
	return (1);
}

void	list_export_helper_2(char *tmp)
{
	printf("%s\n", tmp);
	free(tmp);
}
