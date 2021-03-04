/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:43:54 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/13 13:13:16 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rc/rc.h"

void			z_buffer_clear(t_z_buffer **lst)
{
	t_z_buffer *current;
	t_z_buffer *next;

	if (lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

void			lst_z_add_back(t_z_buffer **alst, t_z_buffer *new)
{
	t_z_buffer *temp;

	if (alst == NULL || new == NULL)
		return ;
	temp = *alst;
	if (*alst)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		*alst = new;
}

t_z_buffer		*lst_z_new(t_raycaster *rc)
{
	t_z_buffer *elem;

	if (!(elem = (t_z_buffer *)malloc(sizeof(t_z_buffer))))
		return (NULL);
	elem->i = rc->column;
	elem->dist = rc->wall_dist_perp;
	elem->next = NULL;
	return (elem);
}

int				store_dist(t_z_buffer **buffer, t_raycaster *rc)
{
	t_z_buffer *new;

	if (!(new = lst_z_new(rc)))
		return (display_error(ENOMEM, NULL));
	lst_z_add_back(buffer, new);
	return (1);
}
