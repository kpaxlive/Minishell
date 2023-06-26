/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:51:17 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:37:56 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_2(void)
{
	int	idx;
	int	**fd;
	int	pid;

	idx = 0;
	fd = NULL;
	if (g_data.args[0][1])
	{
		pid = fork();
		if (!pid)
			redirection(idx);
		waitpid(pid, &g_data.status, 0);
	}
	else
	{
		pid = fork();
		if (!pid)
			run(fd, idx);
		waitpid(pid, &g_data.status, 0);
	}
}

void	prepare(void)
{
	int	**fd;
	int	idx;

	if (g_data.count_l > 1)
	{
		fd = alloc_fd();
		idx = -1;
		while (++idx < g_data.count_l - 1)
			pipe(fd[idx]);
		idx = -1;
		while (++idx < g_data.count_l)
		{
			g_data.pids[idx] = fork();
			if (!g_data.pids[idx])
				run(fd, idx);
		}
		free_fd(fd);
	}
	else if (g_data.count_l == 1)
		prepare_2();
}

void	special(void)
{
	int	line;

	line = g_data.count_l - 1;
	if (!ft_strcmp(g_data.args[line][0][0], "export"))
		export(line);
	else if (!ft_strcmp(g_data.args[line][0][0], "unset"))
		unset(line);
	else if (!ft_strcmp(g_data.args[line][0][0], "cd"))
		cd(line);
	else if (!ft_strcmp(g_data.args[g_data.count_l - 1][0][0], "exit"))
		ft_exit(line);
}

int	check_ret(int ret)
{
	int	x;

	if (!ret)
		return (1);
	if (ret == 1)
	{
		free_ezhel(g_data.path);
		free_ezhel(g_data.pipesplit);
		free(g_data.all_line);
		g_data.status = 258;
	}
	else if (ret == 2)
	{
		free_ezhel(g_data.path);
		free_ezhel(g_data.pipesplit);
		x = -1;
		while (++x < g_data.count_l)
			free_ezhel(g_data.redirsep[x]);
		free(g_data.redirsep);
		free(g_data.all_line);
		g_data.status = 258;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	take_env(envp);
	while (1)
	{
		get_path();
		get_line();
		if (!ft_strlen(g_data.all_line))
		{
			if (g_data.path)
				free_ezhel(g_data.path);
			free(g_data.all_line);
			continue ;
		}
		if (!check_ret(get_data()))
			continue ;
		prepare();
		special();
		free_data();
	}
}
