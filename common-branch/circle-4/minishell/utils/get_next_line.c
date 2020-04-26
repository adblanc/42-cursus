/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:38:24 by fcadet            #+#    #+#             */
/*   Updated: 2019/12/12 19:53:40 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static int		cat_char(t_shell *sh, char c)
{
	int		len;
	char	*new;
	int		i;

	len = 0;
	while (sh->line[len])
		len++;
	if (!(new = ft_malloc(sh, scp_cmd, (len + 2) * sizeof(char))))
		return (-1);
	i = -1;
	while (sh->line[++i])
		new[i] = sh->line[i];
	new[i++] = c;
	new[i] = '\0';
	ft_free(sh, sh->line);
	sh->line = new;
	return (0);
}

int				get_next_line(t_shell *sh, int fd)
{
	char	c;
	int		ret;

	if (fd < 0 || !(sh->line = ft_malloc(sh, scp_cmd, sizeof(char))))
		return (-1);
	*(sh->line) = '\0';
	c = '\0';
	while (c != '\n')
	{
		if ((ret = read(fd, &c, 1)) < 0)
			return (-1);
		if (!ret)
		{
			if (*(sh->line))
				put_str(1, "  \b\b");
			else
			{
				put_str(1, "exit\n");
				return (0);
			}
		}
		else if (cat_char(sh, c) < 0)
			return (-1);
	}
	return (1);
}
