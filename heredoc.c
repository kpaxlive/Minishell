/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:01:31 by dayan             #+#    #+#             */
/*   Updated: 2022/11/27 14:01:32 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_heredoc(int line, int redir)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("> ");
		if (!buffer)
			break ;
		if (!ft_strcmp(buffer, g_data.args[line][redir][1]))
		{
			free(buffer);
			break ;
		}
		ft_putendl_fd(buffer, g_data.pipes[line][1]);
		free(buffer);
	}
}

void	heredoc(void)
{
	int		line;
	int		redir;
	int		tmp_in;

	tmp_in = dup(0);
	g_data.pipes = malloc(sizeof(int *) * g_data.count_l);
	line = -1;
	while (++line < g_data.count_l)
		g_data.pipes[line] = malloc(sizeof(int) * 2);
	line = -1;
	while (g_data.args[++line])
	{
		redir = 0;
		while (g_data.args[line][++redir])
		{
			if (ft_strcmp(g_data.args[line][redir][0], "<<"))
				continue ;
			pipe(g_data.pipes[line]);
			signal(SIGINT, exitheredoc);
			take_heredoc(line, redir);
			close(g_data.pipes[line][1]);
		}
	}
	dup2(tmp_in, 0);
	close(tmp_in);
}
