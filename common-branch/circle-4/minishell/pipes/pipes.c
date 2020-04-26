/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:23:19 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/12 19:52:55 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static int	get_pipes_length(char ***args)
{
	int i;

	i = 0;
	while (args[i][0][0] == '|')
		i++;
	return (i);
}

int			handle_pipes(t_shell *sh)
{
	int		pipes_len;
	int		i;
	int		last_fd;
	int		temp;
	char	***args;

	args = sh->args;
	pipes_len = get_pipes_length(args);
	last_fd = sh->pipe[0];
	i = (last_fd != 0) ? 0 : -1;
	if (last_fd != 0)
		args++;
	while (++i < pipes_len)
	{
		pipe(sh->pipe);
		temp = sh->pipe[0];
		sh->pipe[0] = last_fd;
		execute_command(sh, *args++ + 1);
		close(sh->pipe[1]);
		sh->pipe[1] = 1;
		close(sh->pipe[0]);
		last_fd = temp;
	}
	sh->pipe[0] = last_fd;
	return (pipes_len);
}
