/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:07:52 by dayan             #+#    #+#             */
/*   Updated: 2022/11/29 01:07:53 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_list_helper_1(char **export, int idx)
{
	char	*tmp;

	tmp = ft_strdup(export[idx]);
	free(export[idx]);
	export[idx] = ft_strdup(export[idx + 1]);
	free(export[idx + 1]);
	export[idx + 1] = ft_strdup(tmp);
	free(tmp);
	idx = -1;
}

void	sort_list_helper_2(char **export, int idx)
{
	char	*tmp;

	tmp = ft_strdup(export[idx]);
	free(export[idx]);
	export[idx] = ft_strdup(export[idx + 1]);
	free(export[idx + 1]);
	export[idx + 1] = ft_strdup(tmp);
	free(tmp);
	idx = -1;
}

void	sort_list(char	**export)
{
	int		idx;
	int		j;

	idx = -1;
	while (export[++idx])
	{
		if (export[idx + 1] && export[idx][0] > export[idx + 1][0])
		{
			sort_list_helper_1(export, idx);
			continue ;
		}
		else if (export[idx + 1] && export[idx][0] == export[idx + 1][0])
		{
			j = 1;
			while (export[idx + 1] && export[idx][j] == export[idx + 1][j])
				j++;
			if (export[idx + 1] && export[idx][j] > export[idx + 1][j])
			{
				sort_list_helper_2(export, idx);
				continue ;
			}
		}
	}
}

void	list_export_helper_1(char *tmp, char **tmp_array)
{
	char	*tmp_2;

	tmp_2 = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = ft_strjoin(tmp_2, "\"");
	free(tmp_2);
	tmp_2 = ft_strjoin(tmp, tmp_array[1]);
	free(tmp);
	tmp = ft_strjoin(tmp_2, "\"");
	free(tmp_2);
	printf("%s\n", tmp);
	free(tmp);
}

void	list_export(void)
{
	int		idx;
	char	**tmp_array;
	char	*tmp;
	char	*tmp_2;

	sort_list(g_data.export);
	idx = -1;
	while (g_data.export[++idx])
	{
		tmp_array = ft_split(g_data.export[idx], '=');
		tmp = ft_strjoin("declare -x ", tmp_array[0]);
		if (tmp_array[1])
			list_export_helper_1(tmp, tmp_array);
		else if (ft_strchr(g_data.export[idx], '='))
		{
			tmp_2 = ft_strjoin(tmp, "=\"\"");
			free(tmp);
			printf("%s\n", tmp_2);
			free(tmp_2);
		}
		else
			list_export_helper_2(tmp);
		free_ezhel(tmp_array);
	}
	exit(0);
}
