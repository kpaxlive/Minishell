/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 02:49:58 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:35:37 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int **fd)
{
	int	i;

	i = -1;
	while (++i < g_data.count_l - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

int	**alloc_fd(void)
{
	int	i;
	int	**fd;

	fd = malloc(sizeof(int *) * (g_data.count_l - 1));
	i = -1;
	g_data.pids = malloc(sizeof(int) * g_data.count_l);
	while (++i < g_data.count_l - 1)
		fd[i] = malloc(sizeof(int) * 2);
	return (fd);
}

void	free_fd(int **fd)
{
	int	i;

	close_fd(fd);
	i = -1;
	while (g_data.pids[++i])
		waitpid(g_data.pids[i], &g_data.status, 0);
	free(g_data.pids);
	i = -1;
	while (++i < g_data.count_l - 1)
		free(fd[i]);
	free(fd);
}
