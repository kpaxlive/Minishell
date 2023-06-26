/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 06:37:41 by dayan             #+#    #+#             */
/*   Updated: 2022/12/03 06:37:42 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_commands_helper(char *str, char *command)
{
	char	*tmp;

	if (command)
		tmp = ft_strjoin(command, str);
	else
		tmp = ft_strdup(str);
	free(command);
	command = ft_strdup(tmp);
	free(tmp);
	return (command);
}

void	check_commands(int line)
{
	int		idx;
	int		j;
	char	*command;
	char	**tmp_array;

	command = 0;
	command = check_first_arg(line);
	idx = -1;
	if (command)
		idx++;
	while (g_data.redirsep[line][++idx])
	{
		tmp_array = manuelsplit(g_data.redirsep[line][idx]);
		j = 1;
		while (tmp_array[++j])
		{
			tmp_array[j] = add_space(tmp_array[j]);
			command = check_commands_helper(tmp_array[j], command);
		}
		free_ezhel(tmp_array);
	}
	if (!command)
		command = ft_strdup("echo -n");
	replace_command(line, command, idx);
	free(command);
}

int	check_option(char *str)
{
	int	idx;

	if (str[0] != '-')
		return (0);
	idx = 0;
	while (str[++idx])
		if (str[idx] != 'n')
			return (0);
	return (1);
}

int	redir_sep_helper_3(int line)
{
	int	idx;
	int	redir;

	redir = -1;
	while (g_data.redirsep[line][++redir])
	{
		idx = 0;
		if (g_data.redirsep[line][redir][0] == '>')
		{
			while (g_data.redirsep[line][redir][++idx] == '<'
				|| g_data.redirsep[line][redir][idx] == '>')
				if (g_data.redirsep[line][redir][idx] == '<' || idx >= 2)
					return (print_error("|ragoroliptik|: syntax error", 0));
		}
		else if (g_data.redirsep[line][redir][0] == '<')
		{
			while (g_data.redirsep[line][redir][++idx] == '<'
				|| g_data.redirsep[line][redir][idx] == '>')
				if (g_data.redirsep[line][redir][idx] == '>' || idx >= 3)
					return (print_error("|ragoroliptik|: syntax error", 0));
		}
	}
	return (1);
}

void	trim_spaces(char **str)
{
	int		idx;
	char	*tmp;

	idx = -1;
	while (str[++idx])
	{
		tmp = ft_strtrim(str[idx], " \t\r\v\f\n");
		free(str[idx]);
		str[idx] = ft_strdup(tmp);
		free(tmp);
	}
}
