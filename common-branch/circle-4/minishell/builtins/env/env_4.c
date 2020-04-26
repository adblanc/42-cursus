/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 13:44:50 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/07 17:18:14 by herrfalco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

static void		check_value(t_shell *sh, char *value)
{
	t_var *var;

	var = NULL;
	if (ft_strncmp(value, "$", 1) == 0)
	{
		if (!(var = env_find(sh->env, value + 1, EXPORTED_OR_NOT)))
			return ;
		str_cpy(value, var->value);
	}
}

void			fill_name_value(t_shell *sh,
char name[BUFF], char value[BUFF], char *arg)
{
	int		i;
	int		sep_index;

	i = -1;
	sep_index = char_in_set('=', arg);
	if (sep_index < 0)
	{
		str_cpy(name, arg);
		str_cpy(value, "");
	}
	else
	{
		while (++i < sep_index && *arg)
			name[i] = *(arg++);
		name[i] = '\0';
		i = -1;
		while (*(++arg))
			value[++i] = *arg;
		value[++i] = '\0';
		parse_back_equals(value);
		check_value(sh, value);
	}
}

static void		put_or_modify_arg(t_shell *sh, char **arg)
{
	char	name[BUFF];
	char	value[BUFF];
	t_var	*var;
	t_nv	nv;

	if ((var = env_find(sh->env, *arg, NOT_EXPORTED)))
	{
		var->exported = EXPORTED;
		var->id = env_length(sh->env, EXPORTED);
	}
	else
	{
		fill_name_value(sh, name, value, *arg);
		if (!(var = env_find(sh->env, name, EXPORTED)))
		{
			nv.name = name;
			nv.value = value;
			if (!(var = env_new(sh, &nv,
			env_length(sh->env, EXPORTED), EXPORTED)))
				return ;
			env_add_front(&sh->env, var);
		}
		else
			env_change(var, value);
	}
}

void			env_add_args(t_shell *sh, char **arg)
{
	while (*arg)
	{
		put_or_modify_arg(sh, arg);
		arg++;
	}
}
