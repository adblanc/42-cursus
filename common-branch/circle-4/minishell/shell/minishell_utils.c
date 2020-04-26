/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 20:37:04 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/16 09:06:59 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void	init_shell(t_shell *sh, t_builtins *b, char **envp)
{
	sh->env = NULL;
	sh->mem_list = NULL;
	sh->last_status = 0;
	getcwd(sh->wd, BUFF);
	env_add_args(sh, envp);
	sh->builtins = b;
}

int		check_for_bad_left_operand(char *arg)
{
	int		dollar_i;
	int		equal_i;

	equal_i = char_in_set('=', arg);
	dollar_i = char_in_set('$', arg);
	if (dollar_i >= 0 && equal_i > dollar_i)
		return (0);
	return (1);
}

void	variable_replacement(t_shell *sh, char *var_ptr)
{
	t_var	*var;
	char	variable_name[BUFF];
	size_t	var_name_size;

	while ((var_ptr = ft_strchr(var_ptr, '$')))
	{
		if (*(var_ptr + 1) == CMD)
		{
			var_name_size = variable_name_size(var_ptr + 2);
			strl_cpy(variable_name, var_ptr + 2, var_name_size + 1);
			if ((var = env_find(sh->env, variable_name, EXPORTED_OR_NOT)))
			{
				str_erase_and_concat(var_ptr, var->value, var_name_size + 2);
				var_ptr += str_len(var->value);
			}
			else
				str_cpy(var_ptr, var_ptr + 2 + var_name_size);
		}
		else
		{
			str_cpy(var_ptr + 1, var_ptr + 2);
			var_ptr++;
		}
	}
}

void	status_code_replacement(t_shell *sh, char *var_ptr)
{
	char	status_code[BUFF];

	while ((var_ptr = ft_strchr(var_ptr, '$')))
	{
		if (*(var_ptr + 1) == CMD && *(var_ptr + 2) == '?')
		{
			fill_itoa(status_code, sh->last_status);
			str_erase_and_concat(var_ptr, status_code, 3);
			var_ptr += str_len(status_code);
		}
		else
			var_ptr++;
	}
}

int		set_cmd(t_shell *sh, char **args, char *name, char *value)
{
	t_var		*var;
	int			del_i;
	t_nv		nv;

	del_i = char_in_set('=', *args);
	str_cpy((*args + del_i + 1), (*args + del_i + 2));
	var = NULL;
	fill_name_value(sh, name, value, *args);
	if ((var = env_find(sh->env, name, EXPORTED_OR_NOT)))
	{
		env_change(var, value);
		return (1);
	}
	nv.name = name;
	nv.value = value;
	if (!(var = env_new(sh, &nv,
	999, NOT_EXPORTED)))
		return (0);
	env_add_front(&sh->env, var);
	return (1);
}
