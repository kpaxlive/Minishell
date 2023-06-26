/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:19:13 by dayan             #+#    #+#             */
/*   Updated: 2022/11/26 20:19:15 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(char **str, char *name)
{
	int	x;

	x = -1;
	while (str[++x])
		printf("%s[%d]: X%sX\n", name, x, str[x]);
}

char	*add_space(char *str)
{
	char	*tmp;

	tmp = str;
	str = ft_strjoin(" ", str);
	free(tmp);
	return (str);
}

char	*check_first_arg(int line)
{
	char	*command;

	command = 0;
	if (g_data.redirsep[line][0][0] != '>'
		&& g_data.redirsep[line][0][0] != '<')
		command = ft_strdup(g_data.redirsep[line][0]);
	return (command);
}

int	redir_count(char *str)
{
	int	idx;
	int	counter;

	idx = -1;
	counter = 0;
	while (str[++idx])
	{
		if ((str[idx] == '>' || str[idx] == '<') && !in_quotes(str, idx))
			counter++;
		while (str[idx + 1] && (str[idx] == '>' || str[idx] == '<')
			&& !in_quotes(str, idx))
			idx++;
	}
	return (counter);
}

void	replace_command(int line, char *command, int idx)
{
	char	**holder;
	char	**tmp;
	char	**new;
	int		j;

	holder = alloc_mem(count_arg(g_data.redirsep[line]));
	idx = -1;
	while (g_data.redirsep[line][++idx])
		holder[idx] = ft_strdup(g_data.redirsep[line][idx]);
	free_ezhel(g_data.redirsep[line]);
	new = alloc_mem(redir_count(g_data.pipesplit[line]) + 1);
	new[0] = ft_strdup(command);
	idx = -1;
	if (holder[0][0] != '>' && holder[0][0] != '<')
		idx++;
	j = 0;
	while (holder[++idx])
	{
		tmp = manuelsplit(holder[idx]);
		tmp[1] = add_space(tmp[1]);
		new[++j] = ft_strjoin(tmp[0], tmp[1]);
		free_ezhel(tmp);
	}
	free_ezhel(holder);
	g_data.redirsep[line] = new;
}
