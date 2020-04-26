/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:18:29 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/14 09:44:01 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_lstreverse(t_list **lst)
{
	t_list *prev;
	t_list *current;
	t_list *next;

	if (lst == NULL || *lst == NULL)
		return ;
	prev = NULL;
	current = *lst;
	next = NULL;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*lst = prev;
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list	*temp;
	t_list	*prev;
	t_list	*copy;

	if (lst == NULL || (*f) == NULL)
		return (NULL);
	copy = NULL;
	temp = lst;
	while (temp)
	{
		prev = copy;
		copy = ft_lstnew((*f)(temp->content));
		if (copy == NULL)
			return (NULL);
		copy->next = prev;
		temp = temp->next;
	}
	ft_lstreverse(&copy);
	return (copy);
}
