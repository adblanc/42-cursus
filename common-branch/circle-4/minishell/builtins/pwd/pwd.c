/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:13:07 by herrfalco         #+#    #+#             */
/*   Updated: 2019/12/04 20:15:43 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	pwd(t_shell *sh, char **arg)
{
	if (*arg)
	{
		sh->last_status = 1;
		return (display_error(0, "pwd", ERR_TOO_MANY_ARG));
	}
	put_str(sh->pipe[1], sh->wd);
	put_char(sh->pipe[1], '\n');
	sh->last_status = 0;
}
