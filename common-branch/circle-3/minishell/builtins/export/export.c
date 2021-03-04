/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:46:10 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/04 20:15:33 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	export(t_shell *sh, char **arg)
{
	if (!arg || !(*arg))
	{
		env_list_sort(sh->env, &cmp_by_alpha);
		display_env_list(sh->env, sh->pipe, EXPORT);
	}
	else
		env_add_args(sh, arg);
	sh->last_status = 0;
}
