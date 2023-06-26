/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:51:59 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:37:52 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_env(char **envp)
{
	int	arg_count;
	int	idx;

	arg_count = count_arg(envp);
	g_data.env = malloc(sizeof(char *) * (arg_count + 1));
	g_data.env[arg_count] = 0;
	idx = -1;
	while (envp[++idx])
		g_data.env[idx] = ft_strdup(envp[idx]);
	g_data.export = malloc(sizeof(char *) * (arg_count + 1));
	g_data.export[arg_count] = 0;
	idx = -1;
	while (g_data.env[++idx])
		g_data.export[idx] = ft_strdup(g_data.env[idx]);
}

void	get_path(void)
{
	int		idx;
	char	*tmp;

	idx = -1;
	while (g_data.env[++idx])
	{
		if (!ft_strncmp(g_data.env[idx], "PATH=", ft_strlen("PATH=")))
		{
			g_data.path = ft_split(ft_strchr(g_data.env[idx], '=') + 1, ':');
			idx = -1;
			while (g_data.path[++idx])
			{
				tmp = ft_strdup(g_data.path[idx]);
				free(g_data.path[idx]);
				g_data.path[idx] = ft_strjoin(tmp, "/");
				free(tmp);
			}
			return ;
		}
	}
	g_data.path = NULL;
}
