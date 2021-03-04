/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:36:26 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/07 18:14:37 by herrfalco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static void		exit_with_error(t_shell *sh, int errnum, char *name, char *err)
{
	sh->last_status = 1;
	return (display_error(errnum, name, err));
}

static void		replace(char *from, char *to, char *to_replace_ptr, char **arg)
{
	while (from != to_replace_ptr)
		*to++ = *(from++);
	from += str_len(*arg);
	str_cpy(to, *(arg + 1));
	to += str_len(*(arg + 1));
	while (*from)
		*to++ = *from++;
	*to = '\0';
}

static void		search_and_replace(t_shell *sh, char **arg)
{
	char	replaced[BUFF];
	char	*needle;
	char	*new_args[2];

	new_args[0] = replaced;
	new_args[1] = NULL;
	if (!(needle = ft_strstr(sh->wd, *arg)))
	{
		display_error_with_arg(0, "cd", "string not in pwd", *arg);
		sh->last_status = 1;
		return ;
	}
	else
		replace(sh->wd, replaced, needle, arg);
	return (cd(sh, (char **)new_args));
}

void			cd_home(t_shell *sh, char *old_pwd, char *arg)
{
	char	path[BUFF];
	t_var	*home;

	if (!(home = env_find(sh->env, "HOME", EXPORTED)))
	{
		sh->last_status = 1;
		return ;
	}
	str_cpy(path, home->value);
	if (arg)
		str_cpy(path + str_len(home->value), arg + 1);
	if (chdir(path) != 0)
	{
		sh->last_status = 1;
		return (exit_with_error(sh, errno, "cd", home->value));
	}
	set_old_pwd(sh, old_pwd);
}

void			cd(t_shell *sh, char **arg)
{
	char	old_pwd[BUFF];
	size_t	arg_len;

	arg_len = str_len_2d(arg);
	if (arg_len > 2)
	{
		sh->last_status = 1;
		return (exit_with_error(sh, 0, "cd", ERR_TOO_MANY_ARG));
	}
	else if (arg_len == 2)
		return (search_and_replace(sh, arg));
	if (!getcwd(old_pwd, BUFF))
		return (exit_with_error(sh, errno, "cd", NULL));
	if (!(*arg) || ft_strncmp(*arg, "~", 1) == 0)
		cd_home(sh, old_pwd, *arg);
	else
	{
		if (chdir(*arg) != 0)
			return (exit_with_error(sh, errno, "cd", *arg));
		set_old_pwd(sh, old_pwd);
	}
	set_new_pwd(sh);
	sh->last_status = 0;
}
