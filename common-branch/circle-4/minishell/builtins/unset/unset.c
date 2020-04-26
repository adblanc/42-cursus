/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:12:56 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/04 20:16:00 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	unset(t_shell *sh, char **arg)
{
	if (!arg || !(*arg))
	{
		sh->last_status = 1;
		return (display_error(0, "unset", "not enough arguments"));
	}
	while (*arg)
		env_delete(sh, &(sh->env), *(arg++));
	sh->last_status = 0;
}
