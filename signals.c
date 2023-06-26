/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:56:56 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:38:03 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_export(char	*str)
{
	int		i;
	char	**line;

	i = -1;
	while (g_data.export[++i])
	{
		line = ft_split(g_data.export[i], '=');
		if (!ft_strcmp(line[0], str))
		{
			free_ezhel(line);
			return (i + 1);
		}
		free_ezhel(line);
	}
	return (0);
}

void	signalhandler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
}

void	nothing(int sig)
{
	(void)sig;
	printf("\n");
}

void	exitheredoc(int sig)
{
	(void)sig;
	close(0);
}

void	connectsignals(void)
{
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, SIG_IGN);
}
