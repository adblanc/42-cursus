/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:40:57 by herrfalco         #+#    #+#             */
/*   Updated: 2019/12/07 15:42:14 by herrfalco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static unsigned char	get_hex(char **str)
{
	unsigned char	result;
	int				i;

	(*str) += (**str == '0' ? 2 : 1);
	result = 0;
	i = 2;
	while (i--)
	{
		if (**str >= '0' && **str <= '9')
			result = result * 16 + **str - '0';
		else if (**str >= 'a' && **str <= 'f')
			result = result * 16 + **str + 10 - 'a';
		else if (**str >= 'A' && **str <= 'F')
			result = result * 16 + **str + 10 - 'A';
		else
			break ;
		(*str)++;
	}
	(*str)--;
	return (result);
}

static unsigned char	get_oct(char **str)
{
	unsigned char	result;
	int				i;

	(*str)++;
	result = 0;
	i = 3;
	while ((**str >= '0' && **str <= '7') && i--)
	{
		result = result * 8 + **str - '0';
		(*str)++;
	}
	(*str)--;
	return (result);
}

static int				parse_char(char **str)
{
	if (*(++(*str)) == 'a')
		return ('\a');
	else if (**str == 'b')
		return ('\b');
	else if (**str == 'c')
		return (-1);
	else if (**str == 'e')
		return (27);
	else if (**str == 'f')
		return ('\f');
	else if (**str == 'n')
		return ('\n');
	else if (**str == 'r')
		return ('\r');
	else if (**str == 't')
		return ('\t');
	else if (**str == 'v')
		return ('\v');
	else if ((**str == '0' && *(*str + 1) == 'x') || **str == 'x')
		return (get_hex(str));
	else if (**str == '0')
		return (get_oct(str));
	else
		return (*(--(*str)));
}

static int				echo_str(char *str, int *pipe)
{
	int		c;

	if (!str)
		return (1);
	while (*str)
	{
		if (*str == '\\')
			c = parse_char(&str);
		else
			c = *str;
		if (c < 0)
			return (-1);
		str++;
		put_char(pipe[1], c);
	}
	return (0);
}

void					echo(t_shell *sh, char **arg)
{
	int		ret;
	int		line_ret;

	sh->last_status = 0;
	if (!*arg)
		return (put_char(sh->pipe[1], '\n'));
	if (!(line_ret = !!str_cmp(*arg, "-n")))
		arg++;
	while (!(ret = echo_str(*(arg++), sh->pipe)))
		if (*arg)
			put_char(sh->pipe[1], ' ');
	if (ret > 0 && line_ret)
		put_char(sh->pipe[1], '\n');
}
