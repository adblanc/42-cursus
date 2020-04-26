/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:03:04 by herrfalco         #+#    #+#             */
/*   Updated: 2019/12/19 13:22:11 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static void	print_path(t_shell *sh)
{
	t_var	*home_var;
	t_var	*path_var;
	char	*path;
	char	*home;
	char	*save;

	home_var = env_find(sh->env, "HOME", 1);
	path_var = env_find(sh->env, "PWD", 1);
	home = home_var ? home_var->value : NULL;
	path = path_var ? path_var->value : NULL;
	save = path;
	while (path && home && *home && (*home == *path))
	{
		path++;
		home++;
	}
	if (path && home && !*home)
	{
		put_char(1, '~');
		put_str(1, path);
	}
	else if (save)
		put_str(1, save);
}

static void	print_prompt(t_shell *sh)
{
	t_var *user;

	user = env_find(sh->env, "USER", 1);
	put_str(1, "\033[0;32m");
	if (user)
		put_str(1, user->value);
	put_str(1, "\033[0m");
	put_char(1, ':');
	put_str(1, "\033[1;34m");
	print_path(sh);
	put_str(1, "\033[0;31m");
	put_str(1, " > ");
	put_str(1, "\033[0m");
}

static void	init_builtin(t_builtins *built)
{
	built->fn[0] = &echo;
	str_cpy(built->names[0], "echo");
	built->fn[1] = &cd;
	str_cpy(built->names[1], "cd");
	built->fn[2] = &pwd;
	str_cpy(built->names[2], "pwd");
	built->fn[3] = &export;
	str_cpy(built->names[3], "export");
	built->fn[4] = &unset;
	str_cpy(built->names[4], "unset");
	built->fn[5] = &env;
	str_cpy(built->names[5], "env");
	built->fn[6] = &exit_shell;
	str_cpy(built->names[6], "exit");
}

static t_shell	g_sh;

void		hdl_sig(int sig)
{
	put_str(1, "\b\b  \b\b");
	if (sig == SIGINT)
	{
		*(g_sh.line) = '\0';
		put_char(1, '\n');
		print_prompt(&g_sh);
		g_sh.last_status = 1;
	}
}

int			main(int ac, char **av, char **ag)
{
	t_builtins		built;

	(void)ac;
	(void)av;
	signal(SIGINT, hdl_sig);
	signal(SIGQUIT, hdl_sig);
	init_builtin(&built);
	init_shell(&g_sh, &built, ag);
	while (1)
	{
		print_prompt(&g_sh);
		if (get_next_line(&g_sh, 0) < 1)
			exit_shell(&g_sh, NULL);
		if (!*(g_sh.line))
			continue ;
		if (!(g_sh.args = cut_cmds(&g_sh)))
		{
			g_sh.last_status = EXIT_FAILURE;
			exit_shell(&g_sh, NULL);
		}
		handle_args(&g_sh);
		ft_free_scp(&g_sh, NULL, scp_cmd);
	}
	return (0);
}
