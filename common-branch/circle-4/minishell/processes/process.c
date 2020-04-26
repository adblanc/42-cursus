/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:36:26 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/06 16:38:51 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static void		direct_launch(t_shell *sh, char **args, char **env, int home)
{
	char	commande[BUFF];
	t_var	*home_path;

	home_path = NULL;
	(void)sh;
	if (home)
	{
		if (!(home_path = env_find(sh->env, "HOME", 1)))
		{
			display_error(ENOENT, "minishell", NULL);
			exit_child(sh, EXIT_FAILURE);
		}
		str_cpy(commande, home_path->value);
		str_cpy(commande + str_len(home_path->value), *args + 1);
	}
	else
		str_cpy(commande, *args);
	if (check_file(commande))
	{
		display_error_with_arg(errno, "minishell", *args, NULL);
		exit_child(sh, COMMAND_NOT_FOUND);
	}
	if (execve(commande, args, env) == -1)
		display_error_with_arg(errno, "minishell", *args, NULL);
	exit_child(sh, EXIT_FAILURE);
}

static void		launch(t_shell *sh, char **args, char **env)
{
	if (ft_strncmp(args[0], "./", 2) == 0 ||
	ft_strncmp(args[0], "/", 1) == 0 ||
	ft_strncmp(args[0], "../", 3) == 0)
		direct_launch(sh, args, env, 0);
	else if (ft_strncmp(args[0], "~/", 2) == 0)
		direct_launch(sh, args, env, 1);
	else
		path_launch(sh, args, env);
}

static void		parent_proc(t_shell *sh, pid_t *pid)
{
	int status;

	signal(SIGINT, parent_hdl_sigint);
	waitpid(*pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		waitpid(*pid, &status, WUNTRACED);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			put_str(1, "^\\Quit: 3\n");
		sh->last_status = WTERMSIG(status) + 128;
	}
	else if (WIFEXITED(status))
		sh->last_status = WEXITSTATUS(status);
	signal(SIGINT, hdl_sig);
}

void			launch_process(t_shell *sh, char **args)
{
	pid_t	pid;
	char	**env;

	if (!(env = get_env_list(sh)))
		return (display_error(errno, "minishell", NULL));
	pid = fork();
	if (pid < 0)
		return (display_error(errno, "minishell", NULL));
	if (!pid)
	{
		if (sh->pipe[1] != 1)
			dup2(sh->pipe[1], 1);
		if (sh->pipe[0] != 0)
			dup2(sh->pipe[0], 0);
		launch(sh, args, env);
	}
	else
		parent_proc(sh, &pid);
}
