/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:02:28 by fcadet            #+#    #+#             */
/*   Updated: 2019/12/19 12:03:14 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static int		if_is_quot(char **dst, char **src, char *quot)
{
	if (is_quot(**src))
	{
		if (!*quot)
			*quot = **src;
		else if (*quot == **src)
			*quot = '\0';
		else
			*((*dst)++) = **src;
		return (1);
	}
	return (0);
}

static int		copy_arg(char *dst, char **src)
{
	char	quot;
	int		esc;

	quot = '\0';
	while (**src && (quot || !is_cmd_sep(**src)))
	{
		if (if_is_quot(&dst, src, &quot))
			;
		else if (!quot && is_arg_sep(**src))
			return (*dst = '\0');
		else
		{
			esc = 0;
			if (**src == '\\' && (!quot || is_quot_spe(quot, *((*src) + 1))))
			{
				esc = 1;
				(*src)++;
			}
			*(dst++) = **src;
			if (**src == '$' || **src == '=')
				*(dst++) = (quot == '\'' || esc) ? STR : CMD;
		}
		**src ? (*src)++ : NULL;
	}
	return (*dst = '\0');
}

static int		inc_cmds(char **cmds)
{
	(*cmds)++;
	return (0);
}

static char		**cut_args(t_shell *sh, char **cmds)
{
	char	**args;
	int		count;
	int		i;

	count = arg_count(*cmds);
	i = 0;
	if (!(args = ft_malloc(sh, scp_cmd, (count + 2) * sizeof(char *))))
		return (NULL);
	while (i < count + 1)
		if (!(args[i++] = ft_malloc(sh, scp_cmd, BUFF * sizeof(char))))
			return (NULL);
	args[i] = NULL;
	i = 1;
	while (**cmds && !is_cmd_sep(**cmds))
		is_arg_sep(**cmds) ? inc_cmds(cmds) : copy_arg(args[i++], cmds);
	i = 0;
	args[0][i++] = **cmds ? **cmds : 0;
	if (**cmds == '>' && *((*cmds) + 1) == '>')
		args[0][i++] = *(++(*cmds));
	args[0][i] = '\0';
	return (args);
}

char			***cut_cmds(t_shell *sh)
{
	char	***array;
	int		i;
	int		count;
	char	*cmds;

	cmds = sh->line;
	count = count_cmds(cmds);
	if (!(array = ft_malloc(sh, scp_cmd, (count + 1) * sizeof(char **))))
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (!(array[i++] = cut_args(sh, &cmds)))
			return (NULL);
		if (*cmds)
			cmds++;
	}
	array[i] = NULL;
	return (array);
}
