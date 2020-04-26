/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmds_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:56:36 by herrfalco         #+#    #+#             */
/*   Updated: 2019/12/16 08:58:30 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static void		init_arg_var(t_arg_var *v)
{
	v->count = 0;
	v->quot = '\0';
	v->in = 0;
}

static void		enter_in(int *count, int *in)
{
	(*count)++;
	*in = 1;
}

int				arg_count(char *cmd)
{
	t_arg_var	v;

	init_arg_var(&v);
	while (*cmd && (v.quot || !is_cmd_sep(*cmd)))
	{
		if (is_quot(*cmd))
		{
			if (!v.quot)
			{
				v.quot = *cmd;
				!v.in ? enter_in(&v.count, &v.in) : NULL;
			}
			else if (v.quot == *cmd)
				v.quot = '\0';
		}
		else if (!v.quot && is_arg_sep(*cmd))
			v.in = 0;
		else
		{
			(*cmd == '\\') ? cmd++ : NULL;
			!v.in ? enter_in(&v.count, &v.in) : NULL;
		}
		(*cmd) ? cmd++ : NULL;
	}
	return (v.count);
}

int				count_cmds(char *cmds)
{
	int		count;
	char	quot;

	count = 1;
	quot = 0;
	while (*cmds)
	{
		if (*cmds == '\\')
			cmds++;
		else if (is_quot(*cmds))
		{
			if (!quot)
				quot = *cmds;
			else if (quot == *cmds)
				quot = '\0';
		}
		else if (!quot && is_cmd_sep(*cmds))
		{
			if (*cmds == '>' && *(cmds + 1) == '>')
				cmds++;
			count++;
		}
		*cmds ? cmds++ : NULL;
	}
	return (count);
}
