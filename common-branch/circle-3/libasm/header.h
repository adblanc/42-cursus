/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:09:32 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/20 21:23:14 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>

ssize_t	ft_write(int fildes, const void *buf, size_t nbyte);
ssize_t	ft_read(int fildes, void *buf, size_t nbyte);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char * dst, const char * src);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
#endif
