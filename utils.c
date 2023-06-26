/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:00:47 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:38:07 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(char *input)
{
	int	i;

	i = 0;
	while (input[i])
		if (input[i++] > 32)
			return (1);
	return (0);
}

void	alloc_args(void)
{
	int	x;
	int	i;
	int	redir_countx;

	g_data.args = malloc(sizeof(char ***) * (g_data.count_l + 1));
	g_data.args[g_data.count_l] = 0;
	x = -1;
	while (++x < g_data.count_l)
	{
		redir_countx = redir_count(g_data.pipesplit[x]) + 1;
		g_data.args[x] = malloc(sizeof(char **) * (redir_countx + 1));
		g_data.args[x][redir_countx] = 0;
	}
	x = -1;
	while (g_data.args[++x])
	{
		i = -1;
		while (g_data.redirsep[x][++i])
			g_data.args[x][i] = alloc_mem(find_arg_count(g_data.redirsep[x][i]
						));
	}
}

int	in_quotes(char *str, int i)
{
	int	d_counter;
	int	s_counter;

	d_counter = 0;
	s_counter = 0;
	while (i >= 0 && str[i])
	{
		if (str[i] == '"')
			d_counter++;
		else if (str[i] == 39)
			s_counter++;
		i--;
	}
	if (d_counter % 2 == 0 && s_counter % 2 == 0)
		return (0);
	else if (d_counter % 2 == 0 && s_counter % 2 != 0)
		return (1);
	else if (d_counter % 2 != 0 && s_counter % 2 == 0)
		return (2);
	else if (d_counter % 2 != 0 && s_counter % 2 != 0)
		return (3);
	return (-1);
}

char	**alloc_mem(int size)
{
	char	**str;

	str = malloc(sizeof(char *) * (size + 1));
	str[size] = 0;
	return (str);
}

int	count_arg(char **str)
{
	int	counter;

	counter = 0;
	while (str[++counter])
		;
	return (counter);
}
