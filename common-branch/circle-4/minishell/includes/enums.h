/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 22:58:55 by herrfalco         #+#    #+#             */
/*   Updated: 2019/12/16 08:56:55 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

# include "const.h"

typedef enum	e_mtyp
{
	m_fd,
	m_mal
}				t_mtyp;

typedef enum	e_scop
{
	scp_sh,
	scp_cmd
}				t_scop;

#endif
