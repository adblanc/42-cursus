/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 22:56:39 by herrfalco         #+#    #+#             */
/*   Updated: 2019/12/16 09:08:08 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "enums.h"

typedef struct		s_var
{
	char			name[BUFF];
	char			value[BUFF];
	int				exported;
	size_t			id;
	int				modified;
	struct s_var	*next;
}					t_var;

typedef struct		s_mem
{
	void			*ptr;
	struct s_mem	*next;
	t_scop			scp;
	t_mtyp			mtyp;
}					t_mem;

typedef struct		s_shell
{
	char				wd[BUFF];
	int					pipe[2];
	int					last_status;
	t_mem				*mem_list;
	struct s_builtins	*builtins;
	t_var				*env;
	char				*line;
	char				***args;
}					t_shell;

typedef void		(*t_fn_built_in)(t_shell *, char **);

typedef struct		s_builtins
{
	t_fn_built_in	fn[BUILTIN_NBR];
	char			names[BUILTIN_NBR][BUFF];
}					t_builtins;

typedef struct		s_nv
{
	char	*name;
	char	*value;
}					t_nv;

typedef struct		s_arg_var
{
	int		count;
	char	quot;
	int		in;
}					t_arg_var;

typedef struct		s_red_var
{
	char	***com;
	int		first;
}					t_red_var;

#endif
