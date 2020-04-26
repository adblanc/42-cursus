/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 20:50:38 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/12 19:51:37 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int			check_file(char *path)
{
	struct stat	status_file;

	return (stat(path, &status_file));
}

void		parent_hdl_sigint(int signum)
{
	(void)signum;
	put_char(2, '\n');
}

void		exit_child(t_shell *sh, int status_code)
{
	ft_free_scp(sh, NULL, scp_sh);
	exit(status_code);
}

void		get_command_path(t_shell *sh, char *commande,
	char **path_split, char **args)
{
	char		*ref_ptr;
	int			status;

	ref_ptr = commande;
	while ((status = check_file(commande)))
	{
		if (!path_split || !*path_split)
			break ;
		ref_ptr = commande;
		str_cpy(ref_ptr, "");
		str_cpy(ref_ptr, *path_split);
		ref_ptr += str_len(*path_split);
		str_cpy(ref_ptr++, "/");
		str_cpy(ref_ptr, *args);
		path_split++;
	}
	if (status)
	{
		display_error_with_arg(0, "minishell", *args, "command not found");
		exit_child(sh, COMMAND_NOT_FOUND);
	}
}

void		path_launch(t_shell *sh, char **args, char **env)
{
	char		commande[BUFF];
	char		**path_splitted;
	t_var		*path;

	str_cpy(commande, "");
	path_splitted = NULL;
	path = env_find(sh->env, "PATH", 1);
	if (!path)
	{
		display_error_with_arg(ENOENT, "minishell", *args, NULL);
		exit_child(sh, COMMAND_NOT_FOUND);
	}
	if (!(path_splitted = ft_split(sh, path->value, ':')))
	{
		display_error(ENOMEM, "minishell", NULL);
		exit_child(sh, EXIT_FAILURE);
	}
	get_command_path(sh, commande, path_splitted, args);
	if (execve(commande, args, env) == -1)
		display_error(errno, "minishell", NULL);
	exit_child(sh, EXIT_FAILURE);
}
