/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:49:49 by oorlov            #+#    #+#             */
/*   Updated: 2019/07/23 15:49:50 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int			count_num(size_t a)
{
	int		result;

	result = 0;
	while (a / 10 != 0)
	{
		a /= 10;
		result++;
	}
	return (result);
}

void		omegalul_l(struct stat mystat, t_print t)
{
	int		a;

	a = 0;
	ft_putstr("  ");
	a = count_num(t.count_mem);
	while (a-- > count_num(mystat.st_size))
		ft_putstr(" ");
	ft_putnbr(mystat.st_size);
	ft_putchar(' ');
	print_time(mystat.st_mtime);
}
