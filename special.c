/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:36:52 by dayan             #+#    #+#             */
/*   Updated: 2022/11/24 14:37:03 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_key_env(int idx, int arg_count, int i, int layer)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * arg_count);
	if (!new_env)
		return ;
	new_env = new_env_function(new_env, layer, idx);
	free_ezhel(g_data.env);
	arg_count = count_arg(new_env);
	g_data.env = malloc(sizeof(char *) * (arg_count + 1));
	g_data.env[arg_count] = 0;
	i = -1;
	while (new_env[++i])
		g_data.env[i] = ft_strdup(new_env[i]);
	free_ezhel(new_env);
}

void	unset(int line)
{
	int	idx;
	int	arg_count_env;
	int	arg_count_export;
	int	i;

	idx = 0;
	i = 0;
	while (g_data.args[line][0][++idx])
	{
		if (in_env(g_data.args[line][0][idx]))
		{
			arg_count_env = count_arg(g_data.env);
			remove_key_env(idx, arg_count_env, i, line);
		}
		if (in_export(g_data.args[line][0][idx]))
		{
			arg_count_export = count_arg(g_data.export);
			remove_key_export(idx, arg_count_export, i, line);
		}
	}
}

void	cd(int line)
{
	char	*pwd;
	int		ret;

	ret = 1;
	pwd = getcwd(0, 0);
	ft_setenv("OLDPWD", pwd);
	if (!g_data.args[line][0][1] || !ft_strcmp(g_data.args[line][0][1], "~"))
		ret = chdir(getenv("HOME"));
	if (g_data.args[line][0][1] && !ft_strcmp(g_data.args[line][0][1], "-"))
		ret = return_ret();
	else if (g_data.args[line][0][1] && ft_strcmp(g_data.args[line][0][1], "-"))
		ret = chdir(g_data.args[line][0][1]);
	if (ret)
	{
		free(pwd);
		print_error("no such file or directory: ", g_data.args[line][0][1]);
		g_data.status = 1;
		return ;
	}
	free(pwd);
	pwd = getcwd(0, 0);
	ft_setenv("PWD", pwd);
	free(pwd);
}

void	creat_env(int idx, int line)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * ((count_arg(g_data.env) + 1) + 1));
	new_env[count_arg(g_data.env) + 1] = 0;
	i = -1;
	while (g_data.env[++i])
		new_env[i] = ft_strdup(g_data.env[i]);
	new_env[i] = ft_strdup(g_data.args[line][0][idx]);
	new_env[++i] = 0;
	i = -1;
	free_ezhel(g_data.env);
	g_data.env = malloc(sizeof(char *) * (count_arg(new_env) + 1));
	while (new_env[++i])
		g_data.env[i] = ft_strdup(new_env[i]);
	g_data.env[i] = 0;
	free_ezhel(new_env);
}

void	export(int line)
{
	int		idx;
	char	**arg_sep;

	idx = 0;
	while (g_data.args[line][0][++idx])
	{
		if (!ft_strlen(g_data.args[line][0][idx]))
			continue ;
		arg_sep = ft_split(g_data.args[line][0][idx], '=');
		if (!arg_sep[0] || ft_strchr(arg_sep[0], '?') || isthere_ws(arg_sep[0]))
		{
			print_error("|ragoroliptik|: export: not a valid identifier: ",
				g_data.args[line][0][idx]);
			free_ezhel(arg_sep);
			continue ;
		}
		if (ft_strchr(g_data.args[line][0][idx], '='))
		{
			if (!ft_setenv(arg_sep[0], arg_sep[1]))
				creat_env(idx, line);
		}
		if (!ft_setexport(arg_sep[0], arg_sep[1]))
			create_export(idx, line);
		free_ezhel(arg_sep);
	}
}
