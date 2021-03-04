/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 09:30:03 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/25 16:56:23 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GET_NEXT_LINE_H

# define _GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

int				get_next_line(const int fd, char **line);
char			*ft_malloc_null(void);
char			*ft_str_add_char(char *s1, char c);

#endif
