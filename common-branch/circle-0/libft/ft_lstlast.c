/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:28:52 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/12 14:53:18 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *temp;

	if (lst == NULL)
		return (NULL);
	temp = lst;
	while (temp != NULL && temp->next != NULL)
		temp = temp->next;
	return (temp);
}
