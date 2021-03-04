/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablanc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:26:37 by ablanc            #+#    #+#             */
/*   Updated: 2019/11/21 16:08:27 by ablanc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char	buffer[50];
	int	fd;
	char	text[] = "Hello World!";
	char	text_empty[] = "";

	printf("--- Write avec fd valide ---\n\n");
	printf("=> ft_write : %zd\n", ft_write(1, "Salut 12les amis", 20));
	printf("=> write : %zd\n\n", write(1, "Salut 12les amis", 20));

	printf("--- Write avec fd invalide ---\n\n");
	printf("=> ft_write : %zd\n", ft_write(-1, "Salut 12les amis", 20));
	printf("=> write : %zd\n\n", write(-1, "Salut 12les amis", 20));

	fd = open("test.txt", O_RDONLY);
	printf("--- Read valide ---\n\n");
	printf("=> ft_read : %zd\n", ft_read(fd,buffer , 50));
	fd = open("test1.txt", O_RDONLY);
	printf("=> read: %zd\n\n", read(fd, buffer, 50));

	printf("--- Read invalide ---\n\n");
	fd = open("nonvalid.txt", O_RDONLY);
	printf("=> ft_read : %zd\n", ft_read(fd,buffer , 50));
	printf("=> read : %zd\n", read(fd, buffer, 50));

	printf("--- Strlen valide ---\n\n");
	printf("=> ft_strlen: %zd\n", ft_strlen(text));
	printf("=> strlen: %zd\n", strlen(text));
	printf("--- Strlen with empty text ---\n");
	printf("=> ft_strlen: %zd\n", ft_strlen(text_empty));
	printf("=> strlen: %zd\n", strlen(text_empty));

	printf("--- Strcmp ---\n\n");
	char	cmp11[] = "abcde";
	char	cmp12[] = "abcde";
	char	cmp21[] = "abcd";
	char	cmp22[] = "abcde";
	char	cmp31[] = "abcde";
	char	cmp32[] = "abcd";
	char	cmp41[] = "";
	char	cmp42[] = "";
	char	cmp51[] = "a";
	char	cmp52[] = "c";

	printf("=> strcmp: %d\n", strcmp(cmp11, cmp12));
	printf("=> ft_strcmp: %d\n\n", ft_strcmp(cmp11, cmp12));
	printf("=> strcmp: %d\n", strcmp(cmp21, cmp22));
	printf("=> ft_strcmp: %d\n\n", ft_strcmp(cmp21, cmp22));
	printf("=> strcmp: %d\n", strcmp(cmp31, cmp32));
	printf("=> ft_strcmp: %d\n\n", ft_strcmp(cmp31, cmp32));
	printf("=> strcmp: %d\n", strcmp(cmp41, cmp42));
	printf("=> ft_strcmp: %d\n\n", ft_strcmp(cmp41, cmp42));

	printf("=> strcmp: %d\n", strcmp(cmp51, cmp52));
	printf("=> ft_strcmp: %d\n\n", ft_strcmp(cmp51, cmp52));
	printf("--- Strcpy ---\n\n");
	char cpy1[] = "salutok";
	char cpy2[] = "comment va";
	char cpy11[] = "salutok";
	char cpy22[] = "comment va";
	char cpy3[] = "aaaaaaaaaa";
	char cpy4[] = "salut";
	char cpy33[] = "aaaaaaaaaa";
	char cpy44[] = "salut";
	char cpy5[] = "";
	char cpy6[] = "";
	char cpy55[] = "";
	char cpy66[] = "";
	char cpy7[] = "abcde";
	char cpy8[] = "abcde";
	char cpy77[] = "abcde";
	char cpy88[] = "abcde";
	
	printf("=> strcpy: %s\n", strcpy(cpy22, cpy11));
	printf("=> ft_strcpy: %s\n", ft_strcpy(cpy2, cpy1));
	printf("=> strcpy: %s\n", strcpy(cpy33, cpy44));
	printf("=> ft_strcpy: %s\n", ft_strcpy(cpy3, cpy4));
	printf("=> strcpy: %s\n", strcpy(cpy66, cpy55));
	printf("=> ft_strcpy: %s\n", ft_strcpy(cpy6, cpy5));
	printf("=> strcpy: %s\n", strcpy(cpy88, cpy77));
	printf("=> ft_strcpy: %s\n\n", ft_strcpy(cpy8, cpy7));

	printf("--- Strdup ---\n\n");
	printf("=> strdup: %s\n", strdup("Cela marche"));
	printf("=> ft_strdup: %s\n\n", ft_strdup("Cela marche"));
	return (0);
}
