/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:29:57 by dayan             #+#    #+#             */
/*   Updated: 2022/11/27 18:29:58 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_export(int idx, int line)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * ((count_arg(g_data.export) + 1) + 1));
	new_env[count_arg(g_data.export) + 1] = 0;
	i = -1;
	while (g_data.export[++i])
		new_env[i] = ft_strdup(g_data.export[i]);
	new_env[i] = ft_strdup(g_data.args[line][0][idx]);
	new_env[++i] = 0;
	i = -1;
	free_ezhel(g_data.export);
	g_data.export = malloc(sizeof(char *) * (count_arg(new_env) + 1));
	while (new_env[++i])
		g_data.export[i] = ft_strdup(new_env[i]);
	g_data.export[i] = 0;
	free_ezhel(new_env);
}

int	ft_setexport(char *key, char *value)
{
	int		idx;
	char	*new;
	char	*new_value;

	if (value)
		new_value = ft_strdup(value);
	else
		new_value = ft_strdup("");
	idx = in_export(key);
	if (idx--)
	{
		new = ft_strjoin(key, "=");
		free(g_data.export[idx]);
		g_data.export[idx] = ft_strjoin(new, new_value);
		free(new);
		free(new_value);
		return (1);
	}
	free(new_value);
	return (0);
}
