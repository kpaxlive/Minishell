/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:36:23 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:37:59 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redir(int line, int infd, int outfd)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		if (infd)
		{
			dup2(infd, 0);
			close(infd);
		}
		if (outfd)
		{
			dup2(outfd, 1);
			close(outfd);
		}
		exec(line);
	}
	close(infd);
	close(outfd);
	waitpid(pid, &g_data.status, 0);
}

int	output(int line, int outfd, int redir, int append)
{
	if (outfd)
		close(outfd);
	if (append)
		outfd = open(g_data.args[line][redir][1], O_CREAT | O_RDWR
				| O_APPEND, 0777);
	else
		outfd = open(g_data.args[line][redir][1], O_CREAT | O_RDWR
				| O_TRUNC, 0777);
	return (outfd);
}

int	input(int line, int infd, int redir)
{
	if (infd)
		close(infd);
	infd = open(g_data.args[line][redir][1], O_RDWR, 0777);
	if (infd == -1)
	{
		print_error("|ragoroliptik|: no such file or directory: ",
			g_data.args[line][redir][1]);
		return (-1);
	}
	return (infd);
}

void	redirection(int line)
{
	int	infd;
	int	outfd;
	int	redir;

	redir = 0;
	infd = 0;
	outfd = 0;
	while (g_data.args[line][++redir])
	{
		if (!ft_strcmp(g_data.args[line][redir][0], ">"))
			outfd = output(line, outfd, redir, 0);
		else if (!ft_strcmp(g_data.args[line][redir][0], ">>"))
			outfd = output(line, outfd, redir, 1);
		else if (!ft_strcmp(g_data.args[line][redir][0], "<"))
		{
			infd = input(line, infd, redir);
			if (infd == -1)
				exit(1);
		}
		else if (!ft_strcmp(g_data.args[line][redir][0], "<<")
			|| !ft_strcmp(g_data.args[line][redir][0], "<<<"))
			infd = g_data.pipes[line][0];
	}
	exec_redir(line, infd, outfd);
	exit(g_data.status);
}
