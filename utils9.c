/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:24:36 by dayan             #+#    #+#             */
/*   Updated: 2022/12/01 17:24:38 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_sep_helper_2(int line)
{
	int		i;
	char	**tmp;

	i = 0;
	while (g_data.redirsep[line][++i])
	{
		tmp = manuelsplit(g_data.redirsep[line][i]);
		if (!tmp[1])
		{
			print_error("|ragoroliptik|: syntax error", 0);
			free_ezhel(tmp);
			return (0);
		}
		free_ezhel(tmp);
	}
	return (1);
}

int	redir_sep_helper(int line)
{
	char	**tmp;

	if (g_data.redirsep[line][0][0] == '>'
		|| g_data.redirsep[line][0][0] == '<')
	{
		tmp = manuelsplit(g_data.redirsep[line][0]);
		if (!tmp[1])
		{
			free_ezhel(tmp);
			print_error("|ragoroliptik|: syntax error", 0);
			return (0);
		}
		free_ezhel(tmp);
	}
	if (!redir_sep_helper_2(line))
		return (0);
	return (1);
}

void	tripleredir(void)
{
	int		line;
	int		redir;

	line = -1;
	while (g_data.args[++line])
	{
		redir = 0;
		while (g_data.args[line][++redir]
			&& !ft_strcmp(g_data.args[line][redir][0], "<<<"))
		{
			pipe(g_data.pipes[line]);
			ft_putendl_fd(g_data.args[line][redir][1], g_data.pipes[line][1]);
			close(g_data.pipes[line][1]);
		}
	}
}

void	fix_redirection_helper(int line, int redir, int idx, char *holder)
{
	char	*tmp;

	tmp = ft_strdup(g_data.redirsep[line][redir]);
	free(g_data.redirsep[line][redir]);
	g_data.redirsep[line][redir] = ft_substr(tmp, 0, idx);
	free(tmp);
	tmp = ft_strjoin(g_data.redirsep[line][redir], " ");
	free(g_data.redirsep[line][redir]);
	g_data.redirsep[line][redir] = ft_strjoin(tmp, holder);
	free(tmp);
}

void	ft_exit(int line)
{
	int	status;

	if (!g_data.args[line][0][1])
	{
		free_data();
		free_ezhel(g_data.env);
		exit(0);
	}
	else if (!is_numeric(g_data.args[line][0][1]))
	{
		print_error("|ragoroliptik|: exit: numeric argument required: ",
			g_data.args[line][0][1]);
		free_data();
		free_ezhel(g_data.env);
		exit(255);
	}
	else if (g_data.args[line][0][2])
		print_error("|ragoroliptik|: exit: too many arguments", 0);
	else
	{
		status = ft_atoi(g_data.args[line][0][1]);
		free_data();
		free_ezhel(g_data.env);
		exit(status);
	}
}
