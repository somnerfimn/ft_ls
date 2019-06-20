/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subfunction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 05:46:32 by oorlov            #+#    #+#             */
/*   Updated: 2019/06/20 05:46:34 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void						ft_putchar(char c)
{
	write(1, &c, 1);
}

void						ft_putstr(char *str)
{
	int						count;

	count = 0;
	while (str[count])
		write(1, &str[count++], 1);
}

void						ft_putendl(char *s)
{
	if (s)
	{
		ft_putstr(s);
		write(1, "\n", 1);
	}
}

void						ft_putnbr(int n)
{
	if (n < -9 || n > 9)
		ft_putnbr(n / 10);
	if (n < 0)
	{
		if (n >= -9)
		{
			ft_putchar('-');
		}
		ft_putchar('0' - (n % 10));
	}
	else
		ft_putchar('0' + (n % 10));
}

int							ft_strcmp(const char *s1, const char *s2)
{
	int						tmp;
	unsigned char			*str1;
	unsigned char			*str2;

	tmp = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (str1[tmp] == str2[tmp])
	{
		if (str1[tmp] == '\0')
			return (0);
		tmp++;
	}
	return (str1[tmp] - str2[tmp]);
}
