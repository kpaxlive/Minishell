/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:36:57 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:35:25 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(void)
{
	int	idx;
	int	arg_count;

	idx = -1;
	arg_count = count_arg(g_data.env);
	while (++idx < arg_count)
		printf("%s\n", g_data.env[idx]);
	exit(0);
}

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	printf("%s\n", pwd);
	free(pwd);
	exit(0);
}

void	echo(int line)
{
	int	idx;
	int	n;

	idx = 0;
	n = 1;
	if (g_data.args[line][0][1] && check_option(g_data.args[line][0][1]))
	{
		n = 0;
		idx = 1;
	}
	while (g_data.args[line][0][++idx])
	{
		printf("%s", g_data.args[line][0][idx]);
		if (g_data.args[line][0][idx + 1])
			printf(" ");
	}
	if (n)
		printf("\n");
	exit(0);
}

void	builtins(int line)
{
	if (!ft_strcmp(g_data.args[line][0][0], "env"))
		env();
	else if (!ft_strcmp(g_data.args[line][0][0], "pwd"))
		pwd();
	else if (!ft_strcmp(g_data.args[line][0][0], "echo"))
		echo(line);
	else if (!ft_strcmp(g_data.args[line][0][0], "export")
		&& !g_data.args[line][0][1])
		list_export();
	else if (!ft_strcmp(g_data.args[line][0][0], "export")
		|| !ft_strcmp(g_data.args[line][0][0], "unset")
		|| !ft_strcmp(g_data.args[line][0][0], "cd")
		|| !ft_strcmp(g_data.args[line][0][0], "exit"))
		exit(0);
}
