/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:51:39 by dayan             #+#    #+#             */
/*   Updated: 2022/11/08 13:51:39 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include "libft/libft.h"
# include <fcntl.h>

typedef struct s_data
{
	int		*pids;
	int		**pipes;
	int		*specials;
	int		count_l;
	int		status;
	char	**env;
	char	**export;
	char	**path;
	char	*all_line;
	char	**pipesplit;
	char	***redirsep;
	char	****args;
}	t_data;

t_data	g_data;

//	redirection.c
void	redirection(int line);

//	builtins.c
void	env(void);
void	pwd(void);
void	builtins(int line);

//	run.c
void	set_fd(int **fd, int line);
void	no_builtins(int line);
void	exec(int line);
void	run(int **fd, int line);
int		sum(int idx, char **old);

//	get_line.c
char	*take_line(void);
char	*get_input(void);
void	get_line(void);

//	get_redirsep.c
int		find_redir(char *str);
int		find_redir_count(char *str);
char	**redirsplit(char *str, int idx, int j);
int		get_redirsep(void);

//	get_data.c
int		count_pipe(char *str);
char	**manuelsplit(char *str);
void	fill_pipesplit(char **new, int line);
int		get_data(void);

//	get_path.c
void	take_env(char **envp);
void	get_path(void);

//	main.c
void	special(void);
void	prepare(void);

//	pipesplit.c
int		find_pipe(char *str, int idx);
void	pipesplit(char *str);

//	signals.c
int		in_export(char	*str);
void	connectsignals(void);
void	nothing(int sig);
void	exitheredoc(int sig);
void	signalhandler(int sig);

//	special.c
void	unset(int line);
void	cd(int line);
void	export(int line);

//	list_export.c
void	take_list(int idx, char **export);
void	list_export(void);

//	take_args.c
void	argsplit(char *str, int x);
void	take_args(void);

//	heredoc.c
void	heredoc(void);
int		func_helper_2(int *counter, int *idx, char **new, char **args);

//	utils.c
int		is_command(char *input);
void	alloc_args(void);
int		in_quotes(char *str, int i);
char	**alloc_mem(int size);
int		count_arg(char **str);

//	utils2.c
int		find_arg_count(char *str);
void	free_ezhel(char **str);
void	free_data(void);
int		in_env(char	*str);
int		ft_setenv(char *key, char *value);

//	utils3.c
int		count_char(char *str, char x);
int		find_size(char *str, char c);
char	**dollarsplit(char *str, char x);
int		find_key_size(char *str);
int		is_ws(char c);

// utils4.c
int		print_error(char *str, char *variable);
void	check_files(int line);
int		return_ret(void);
char	**new_env_function(char **new_env, int layer, int idx);
int		find_ws_arg(char *str, int idx);

//	utils5.c
char	*fill_tmp(int line, int redir, int arg, char *tmp);
char	*get_value(char *key);
char	*get_new(char *old_str, char *new);
char	*get_new_2(char *old_str, char *new);
void	free_new(int line, int redir, int arg, char *new);

// utils6.c
void	print_args(char **str, char *name);
char	*add_space(char *str);
char	*check_first_arg(int line);
int		redir_count(char *str);
void	replace_command(int line, char *command, int idx);

//	utils7.c
void	create_export(int idx, int line);
int		ft_setexport(char *key, char *value);

//	utils8.c
char	**new_export_function(char **new_env, int layer, int idx);
int		isthere_ws(char *str);
void	remove_key_export(int idx, int arg_count, int i, int layer);
int		is_numeric(char *str);
void	list_export_helper_2(char *tmp);

//	utils9.c
int		redir_sep_helper(int line);
void	tripleredir(void);
void	fix_redirection_helper(int line, int redir, int idx, char *holder);
void	ft_exit(int line);

//	utils10.c
void	check_commands(int line);
int		check_option(char *str);
int		redir_sep_helper_3(int line);
void	trim_spaces(char **str);

//	fd.c
void	close_fd(int **fd);
int		**alloc_fd(void);
void	free_fd(int **fd);

#endif
