/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:08:34 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/16 09:09:16 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_H
# define HEADERS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/errno.h>
# include "structs.h"

/*
**	mem handling
*/
void	*ft_malloc(t_shell *sh, t_scop scp, unsigned int size);
void	ft_free(t_shell *sh, void *ptr);
void	ft_free_scp(t_shell *sh, t_mem *mem, t_scop scp);

/*
**	shell related
*/
void	launch_process(t_shell *sh, char **args);
void	execute_command(t_shell *sh, char **args);
int		redir_left(t_shell *sh, char ***par);
int		redir_right(t_shell *sh, char ***par);
int		handle_pipes(t_shell *sh);
void	check_for_variable(t_shell *sh, char **args);
void	handle_args(t_shell *sh);
void	init_shell(t_shell *sh, t_builtins *b, char **envp);

/*
**	process utils
*/
void	path_launch(t_shell *sh, char **args, char **env);
void	get_command_path(t_shell *sh, char *commande,
char	**path_split, char **args);
int		check_file(char *path);
void	init_pipe(t_shell *sh);
void	exit_child(t_shell *sh, int status_code);

/*
**	utils
*/
void	put_char(int fd, char c);
void	put_str(int fd, char *str);
int		str_cmp(char *s1, char *s2);
char	*str_cpy(char *dst, const char *src);
int		char_in_set(char c, char *charset);
void	display_error(int errnum, char *name, char *error);
void	display_error_with_arg(int errnum, char *name, char *arg, char *err);
size_t	str_len_2d(char	**tab);
int		ft_atoi(const char *str);
size_t	str_len(const char *s);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		get_next_line(t_shell *sh, int fd);
char	***cut_cmds(t_shell *sh);
char	**ft_split(t_shell *sh, char const *s, char c);
void	parse_back_equals(char *str);
size_t	variable_name_size(char *variable);
size_t	strl_cpy(char *dst, const char *src, size_t size);
void	str_erase_and_concat(char *dest, char const *src, size_t len);
char	**check_all_args_for_equals(char **args);
void	fill_itoa(char *str, int n);
void	close_pipe(t_shell *sh);

/*
**	minishell utils
*/
int		check_for_bad_left_operand(char *arg);
void	variable_replacement(t_shell *sh, char *var_ptr);
void	status_code_replacement(t_shell *sh, char *var_ptr);
int		set_cmd(t_shell *sh, char **args, char *name, char *value);

/*
**	cut_cmds utils
*/
int		is_quot_spe(char quot, char c);
int		is_arg_sep(char c);
int		is_cmd_sep(char c);
int		is_quot(char c);
int		arg_count(char *cmd);
int		count_cmds(char *cmds);

/*
**	env linked_list
*/
size_t	env_length(t_var *env, int exported);
t_var	*env_new(t_shell *sh, t_nv *nv, size_t id, int exported);
void	env_add_front(t_var **aenv, t_var *new);
t_var	*env_find(t_var *env, char *name, int exported);
void	env_change(t_var *var, char *value);
void	env_list_sort(t_var *env, int cmp(t_var *, t_var *));
void	env_delete(t_shell *sh, t_var **aenv, char *name);

/*
**	env variables
*/
void	env_add_args(t_shell *sh, char **arg);
void	display_env_list(t_var *env, int *pipe, int mode);
int		cmp_by_id(t_var *a, t_var *b);
int		cmp_by_alpha(t_var *a, t_var *b);
char	**get_env_list(t_shell *sh);
void	set_new_pwd(t_shell *sh);
void	set_old_pwd(t_shell *sh, char *old_pwd);
void	fill_name_value(t_shell *sh, char name[BUFF],
char value[BUFF], char *arg);

/*
**	build-in
*/
void	echo(t_shell *sh, char **arg);
void	cd(t_shell *sh, char **arg);
void	pwd(t_shell *sh, char **arg);
void	export(t_shell *sh, char **arg);
void	unset(t_shell *sh, char **arg);
void	env(t_shell *sh, char **arg);
void	exit_shell(t_shell *sh, char **arg);

/*
**	signals handling
*/
void	hdl_sig(int sig);
void	parent_hdl_sigint(int signum);
void	parent_hdl_sigdump(int signum);

#endif
