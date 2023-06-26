/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 03:36:25 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:38:01 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sum(int idx, char **old)
{
	int	idx_sum;

	idx_sum = 0;
	while (--idx >= 0)
		idx_sum += ft_strlen(old[idx]);
	return (idx_sum);
}

void	set_fd(int **fd, int line)
{
	if (line == 0)
		dup2(fd[line][1], 1);
	else if (line < g_data.count_l - 1)
	{
		dup2(fd[line - 1][0], 0);
		dup2(fd[line][1], 1);
	}
	else if (line == g_data.count_l - 1)
		dup2(fd[line - 1][0], 0);
	close_fd(fd);
}

void	no_builtins(int line)
{
	int		idx;
	char	*cmd;

	if (!g_data.path)
		return ;
	idx = -1;
	while (g_data.path[++idx])
	{
		cmd = ft_strjoin(g_data.path[idx], g_data.args[line][0][0]);
		if (!access(cmd, F_OK))
			execve(cmd, g_data.args[line][0], g_data.env);
		free(cmd);
	}
}

void	exec(int line)
{
	if (ft_strchr(g_data.args[line][0][0], '/')
		&& !access(g_data.args[line][0][0], F_OK))
		execve(g_data.args[line][0][0], g_data.args[line][0], g_data.env);
	builtins(line);
	no_builtins(line);
	print_error("|ragoroliptik|: command not found: ", g_data.args[line][0][0]);
	exit(127);
}

void	run(int **fd, int line)
{
	signal(SIGQUIT, exitheredoc);
	if (g_data.count_l > 1)
		set_fd(fd, line);
	if (g_data.args[line][1])
	{
		redirection(line);
		if (line == g_data.count_l - 1)
			exit(0);
	}
	exec(line);
}
