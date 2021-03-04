/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:51:07 by ablanc            #+#    #+#             */
/*   Updated: 2019/12/12 19:50:22 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void				env_delete(t_shell *sh, t_var **aenv, char name[BUFF])
{
	t_var *prev;
	t_var *temp;

	temp = *aenv;
	if (!str_cmp(name, temp->name))
	{
		*aenv = temp->next;
		ft_free(sh, temp);
		return ;
	}
	while (temp && str_cmp(name, temp->name))
	{
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	prev->next = temp->next;
	ft_free(sh, temp);
}

int					cmp_by_id(t_var *a, t_var *b)
{
	return (a->id - b->id);
}

int					cmp_by_alpha(t_var *a, t_var *b)
{
	return (str_cmp(a->name, b->name));
}

static void			swap_var(t_var *a, t_var *b)
{
	int		exported;
	int		modified;
	size_t	id;
	char	name[BUFF];
	char	value[BUFF];

	modified = a->modified;
	exported = a->exported;
	id = a->id;
	str_cpy(name, a->name);
	str_cpy(value, a->value);
	a->exported = b->exported;
	a->id = b->id;
	a->modified = b->modified;
	str_cpy(a->name, b->name);
	str_cpy(a->value, b->value);
	b->exported = exported;
	b->id = id;
	b->modified = modified;
	str_cpy(b->name, name);
	str_cpy(b->value, value);
}

void				env_list_sort(t_var *env, int cmp(t_var *, t_var *))
{
	t_var		*ptr_1;
	t_var		*last_ptr;
	int			swapped;

	swapped = 1;
	ptr_1 = env;
	last_ptr = NULL;
	if (!env)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr_1 = env;
		while (ptr_1->next != last_ptr)
		{
			if (cmp(ptr_1, ptr_1->next) > 0)
			{
				swap_var(ptr_1, ptr_1->next);
				swapped = 1;
			}
			ptr_1 = ptr_1->next;
		}
		last_ptr = ptr_1;
	}
}
