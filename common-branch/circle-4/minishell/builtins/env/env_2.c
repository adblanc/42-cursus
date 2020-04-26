/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:15:49 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/05 18:00:32 by herrfalco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

size_t	env_length(t_var *env, int exported)
{
	size_t	i;
	t_var	*temp;

	temp = env;
	i = 0;
	while (temp)
	{
		if (exported == EXPORTED_OR_NOT || exported == temp->exported)
			i++;
		temp = temp->next;
	}
	return (i);
}

t_var	*env_new(t_shell *sh, t_nv *nv, size_t id, int exported)
{
	t_var *var;

	var = (t_var *)ft_malloc(sh, scp_sh, sizeof(t_var));
	if (!var)
		return (NULL);
	var->exported = exported;
	var->id = id;
	var->modified = 0;
	str_cpy(var->name, nv->name);
	str_cpy(var->value, nv->value);
	var->next = NULL;
	return (var);
}

void	env_add_front(t_var **aenv, t_var *new)
{
	if (!aenv || !new)
		return ;
	new->next = *aenv;
	*aenv = new;
}

t_var	*env_find(t_var *env, char *name, int exported)
{
	t_var *temp;

	temp = env;
	if (!temp)
		return (NULL);
	while (temp)
	{
		if (!str_cmp(temp->name, name) &&
		(temp->exported == exported || exported == EXPORTED_OR_NOT))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	env_change(t_var *var, char *value)
{
	if (!var)
		return ;
	str_cpy(var->value, value);
	var->modified = 1;
}
