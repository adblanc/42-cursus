/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:47:53 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/04 20:14:53 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	display_env_list(t_var *env, int *pipe, int mode)
{
	t_var *temp;

	temp = env;
	if (!temp)
		return ;
	while (temp)
	{
		if (temp->exported &&
		(mode != ENV || temp->modified || !!str_cmp(temp->value, "")))
		{
			put_str(pipe[1], temp->name);
			put_char(pipe[1], '=');
			if (mode == EXPORT && !str_cmp(temp->value, ""))
				put_str(pipe[1], "''");
			else
				put_str(pipe[1], temp->value);
			put_char(pipe[1], '\n');
		}
		temp = temp->next;
	}
}

void	env(t_shell *sh, char **arg)
{
	if (str_len_2d(arg) > 1)
	{
		sh->last_status = 1;
		return (display_error(0, "env", ERR_TOO_MANY_ARG));
	}
	env_list_sort(sh->env, &cmp_by_id);
	display_env_list(sh->env, sh->pipe, ENV);
	sh->last_status = 0;
}
