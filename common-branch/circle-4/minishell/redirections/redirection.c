/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:43:38 by herrfalco         #+#    #+#             */
/*   Updated: 2019/12/19 12:21:31 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static char		**append_args(t_shell *sh, char **old, char **to_append)
{
	int		len1;
	int		len2;
	char	**result;
	char	**old_sav;
	int		i;

	len1 = str_len_2d(old);
	len2 = str_len_2d(to_append);
	old_sav = old;
	if (!(result = ft_malloc(sh, scp_cmd, (len1 + len2 + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	if (len1)
		while (*old)
			result[i++] = *(old++);
	if (len2)
		while (*to_append)
			result[i++] = *(to_append++);
	result[i] = NULL;
	if (old_sav)
		ft_free(sh, old_sav);
	return (result);
}

static int		exec_red(t_shell *sh, char ***par, t_red_var *var)
{
	int		new_pipe[2];

	if (!str_cmp(**(sh->args), "|"))
	{
		pipe(new_pipe);
		if (sh->pipe[1] == 1)
			sh->pipe[1] = new_pipe[1];
		else
			close(new_pipe[1]);
	}
	if (var->first)
	{
		*(*(var->com) + 1) ? execute_command(sh, *par) : NULL;
		ft_free(sh, *par);
		*par = NULL;
		close_pipe(sh);
		if (!str_cmp(**(sh->args), "|"))
		{
			sh->pipe[0] = new_pipe[0];
			sh->args--;
		}
		else
			init_pipe(sh);
	}
	return (1);
}

static int		return_error(t_shell *sh, int errnum, char *err, char ***par)
{
	int		new_pipe[2];

	if (errnum)
		display_error_with_arg(errnum, "minishell", *(*(sh->args) + 1), NULL);
	else
		display_error(0, "minishell", err);
	close_pipe(sh);
	while (!str_cmp(**(sh->args), "<") || !str_cmp(**(sh->args), ">")
		|| !str_cmp(**(sh->args), ">>"))
		sh->args++;
	if (!str_cmp(**(sh->args), "|"))
	{
		pipe(new_pipe);
		close(new_pipe[1]);
		sh->pipe[0] = new_pipe[0];
		sh->args--;
	}
	else
		init_pipe(sh);
	ft_free(sh, *par);
	*par = NULL;
	return (0);
}

int				redir_left(t_shell *sh, char ***par)
{
	t_red_var	var;

	var.com = sh->args;
	var.first = *par ? 0 : 1;
	if (var.first)
		if (!(*par = append_args(sh, *par, *(var.com) + 1)))
			return (0);
	while (!str_cmp(**(sh->args), "<"))
	{
		sh->args++;
		sh->pipe[0] != 0 ? (void)close(sh->pipe[0]) : NULL;
		if (!*(*(sh->args) + 1) && (sh->last_status = 258))
			return (return_error(sh, 0, ERR_TOKEN_NL, par));
		sh->pipe[0] = open(*(*(sh->args) + 1), O_RDONLY);
		if (sh->pipe[0] < 0)
			return (return_error(sh, errno, NULL, par));
		if (*(*(sh->args) + 2))
			if (!(*par = append_args(sh, *par, *(sh->args) + 2)))
				return (0);
	}
	if (!str_cmp(**(sh->args), ">") || !str_cmp(**(sh->args), ">>"))
		if (!redir_right(sh, par))
			return (0);
	return (exec_red(sh, par, &var));
}

int				redir_right(t_shell *sh, char ***par)
{
	t_red_var	var;

	var.com = sh->args;
	var.first = *par ? 0 : 1;
	if (var.first && !(*par = append_args(sh, *par, *(var.com) + 1)))
		return (0);
	while (!str_cmp(**(sh->args), ">") || !str_cmp(**(sh->args), ">>"))
	{
		sh->args++;
		sh->pipe[1] != 1 ? (void)close(sh->pipe[1]) : NULL;
		if (!*(*(sh->args) + 1) && (sh->last_status = 258))
			return (return_error(sh, 0, ERR_TOKEN_NL, par));
		sh->pipe[1] = !str_cmp(**(sh->args - 1), ">>") ?
			open(*(*(sh->args) + 1), O_WRONLY | O_CREAT | O_APPEND, 0666)
			: open(*(*(sh->args) + 1), O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (sh->pipe[1] < 0)
			return (return_error(sh, errno, NULL, par));
		if (*(*(sh->args) + 2))
			if (!(*par = append_args(sh, *par, *(sh->args) + 2)))
				return (0);
	}
	if (!str_cmp(**(sh->args), "<") && !redir_left(sh, par))
		return (0);
	return (exec_red(sh, par, &var));
}
