/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:32:02 by herrfalco         #+#    #+#             */
/*   Updated: 2019/12/07 18:01:46 by herrfalco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

void			*ft_malloc(t_shell *sh, t_scop scp, unsigned int size)
{
	t_mem	*new;

	if (!(new = malloc(sizeof(t_mem))))
		return (new);
	if (!(new->ptr = malloc(size)))
	{
		free(new);
		return (NULL);
	}
	new->next = sh->mem_list;
	sh->mem_list = new;
	new->scp = scp;
	new->mtyp = m_mal;
	return (new->ptr);
}

static void		ft_free_mtyp(t_mem *mem)
{
	free(mem->ptr);
	free(mem);
}

void			ft_free(t_shell *sh, void *ptr)
{
	t_mem	*mem;
	t_mem	*tmp;

	mem = sh->mem_list;
	if (mem->ptr == ptr)
	{
		sh->mem_list = mem->next;
		ft_free_mtyp(mem);
		return ;
	}
	while (mem->next->ptr != ptr)
		mem = mem->next;
	tmp = mem->next;
	mem->next = mem->next->next;
	ft_free_mtyp(tmp);
}

void			ft_free_scp(t_shell *sh, t_mem *mem, t_scop scp)
{
	t_mem	*tmp;

	if (!mem)
	{
		if (!sh->mem_list)
			return ;
		if (sh->mem_list->next)
			ft_free_scp(sh, sh->mem_list, scp);
		if (sh->mem_list->scp == scp || scp == scp_sh)
		{
			tmp = sh->mem_list;
			sh->mem_list = tmp->next;
			ft_free_mtyp(tmp);
		}
	}
	else
	{
		mem->next->next ? ft_free_scp(sh, mem->next, scp) : NULL;
		if (mem->next->scp == scp || scp == scp_sh)
		{
			tmp = mem->next;
			mem->next = tmp->next;
			ft_free_mtyp(tmp);
		}
	}
}
