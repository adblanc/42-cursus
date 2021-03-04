/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:30:49 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/04 20:19:32 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	check_for_variable(t_shell *sh, char **args)
{
	char	*var_ptr;

	while (*args)
	{
		var_ptr = *args;
		status_code_replacement(sh, var_ptr);
		variable_replacement(sh, var_ptr);
		args++;
	}
}

char	**check_for_export(t_shell *sh, char **args)
{
	char		name[BUFF];
	char		value[BUFF];
	int			del_i;
	char		**args_ref;

	args_ref = args;
	while (*args)
	{
		del_i = char_in_set('=', *args);
		if (del_i < 0 || !check_for_bad_left_operand(*args))
			return (check_all_args_for_equals(args));
		if (*(*args + del_i + 1) == STR)
		{
			str_cpy((*args + del_i + 1), (*args + del_i + 2));
			return (args);
		}
		else if (*(*args + del_i + 1) == CMD)
		{
			if (!set_cmd(sh, args, name, value))
				return (NULL);
			args_ref++;
		}
		args++;
	}
	return (args_ref);
}

void	execute_command(t_shell *sh, char **args)
{
	int		i;

	i = -1;
	if (!*args)
		return ;
	if (!(args = check_for_export(sh, args)))
		return (display_error(ENOMEM, "minishell", NULL));
	check_for_variable(sh, args);
	while (++i < BUILTIN_NBR)
	{
		if (*args && str_cmp(*args, sh->builtins->names[i]) == 0)
			return ((*(*sh->builtins).fn[i])(sh, args + 1));
	}
	if (*args)
		return (launch_process(sh, args));
}
