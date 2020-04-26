/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <ablanc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 10:55:56 by ablanc            #+#    #+#             */
/*   Updated: 2019/10/24 10:44:00 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H

# define _FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

# define LEFT 0
# define RIGHT 1

# define PADDING 2
# define PRECISION 3

# define NULL_SIZE 6

typedef struct	s_list
{
	char		*res;
	int			count;

	int			is_num;

	int			flags_to_skip;
	int			is_neg;

	int			minus;
	int			padding;
	int			zero;

	int			precision;

	int			end;
}				t_list;

/*
**	MAIN FUNCTIONS
*/
int				ft_printf(const char *str, ...);
int				ft_parse_flags(const char *s, t_list *status, va_list ap);
void			ft_status_init(t_list *status);
/*
**	CHECK AND CORRECT FUNCTIONS
*/
int				ft_check_status(const char *s, t_list *status, va_list ap);
size_t			ft_check_flags_length(const char *s);
void			ft_correct_flags(t_list *status);
void			ft_correct_precision_zero(t_list *status);
/*
**	CONVERT FUNCTIONS
*/
char			*ft_conv_int(int n, t_list *status);
char			*ft_conv_unsigned_int(int n, t_list *status);
char			*ft_conv_string(const char *s1, t_list *status);
char			*ft_conv_base(unsigned int n, char *base, t_list *status);
char			*ft_conv_char(char c);
char			*ft_conv_addr(void *ptr, t_list *status);
/*
**	PRINT FUNCTIONS
*/
void			ft_print_padding(t_list *status, int side);
void			ft_print_precision(t_list *status);
void			ft_print_string(t_list *status);
void			ft_print_hex(t_list *status);
void			ft_print_int(t_list *status);
void			ft_print_unsigned_int(t_list *status);
void			ft_print_addr(t_list *status);
void			ft_print_char(t_list *status);
void			ft_print_char_special(char c, t_list *status);
/*
**	MISC FUNCTIONS
*/
void			ft_putchar(char c, t_list *status);
void			ft_putstr(char *str, t_list *status);
size_t			ft_strlen(const char *s);
int				ft_isdigit(int c);

#endif
