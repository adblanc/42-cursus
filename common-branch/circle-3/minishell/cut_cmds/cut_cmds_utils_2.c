/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cmds_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 13:44:49 by herrfalco         #+#    #+#             */
/*   Updated: 2019/12/04 20:16:55 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

int		is_quot_spe(char quot, char c)
{
	if (quot == '\"' && (c == '\\' || c == '$' || c == '`' || c == '"'
		|| c == '\\'))
		return (1);
	return (0);
}

int		is_arg_sep(char c)
{
	if (c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int		is_cmd_sep(char c)
{
	if (c == ';' || c == '|' || c == '<'
		|| c == '>')
		return (1);
	return (0);
}

int		is_quot(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}
