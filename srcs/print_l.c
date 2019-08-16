/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 05:50:42 by oorlov            #+#    #+#             */
/*   Updated: 2019/06/20 05:50:44 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void				type_file_l(struct stat mystat)
{
	if (S_ISLNK(mystat.st_mode))
		ft_putstr("l");
	else if (S_ISDIR(mystat.st_mode))
		ft_putstr("d");
	else if (S_ISREG(mystat.st_mode))
		ft_putstr("-");
	else if (S_ISSOCK(mystat.st_mode))
		ft_putstr("s");
	else if (S_ISCHR(mystat.st_mode))
		ft_putstr("c");
	else if (S_ISBLK(mystat.st_mode))
		ft_putstr("b");
}

int					itoo(int decimal_n)
{
	int				result;
	int				count_10;
	int				tmp;

	count_10 = 1;
	tmp = 0;
	result = 0;
	while (decimal_n != 0)
	{
		tmp = decimal_n % 8;
		result += tmp * count_10;
		count_10 *= 10;
		decimal_n /= 8;
	}
	return (result);
}

void				write_access(int num)
{
	if (num == 0)
		ft_putstr("---");
	else if (num == 1)
		ft_putstr("--x");
	else if (num == 2)
		ft_putstr("-w-");
	else if (num == 3)
		ft_putstr("-wx");
	else if (num == 4)
		ft_putstr("r--");
	else if (num == 5)
		ft_putstr("r-x");
	else if (num == 6)
		ft_putstr("rw-");
	else if (num == 7)
		ft_putstr("rwx");
}

void				print_time(time_t time_m)
{
	int				count;
	char			*mod_time;

	count = 3;
	mod_time = ctime(&time_m);
	if (time(NULL) - time_m < 15768000)
		while (count++ != 15)
			ft_putchar(mod_time[count]);
	else
	{
		while (count++ != 10)
			ft_putchar(mod_time[count]);
		ft_putchar('\t');
		count = 19;
		while (count++ != 23)
			ft_putchar(mod_time[count]);
	}
	ft_putstr(" ");
}

void				access_rights(struct stat mystat, t_print t)
{
	struct passwd	*pw;
	struct group	*gr;
	int				iaccess;
	int				a;

	pw = getpwuid(mystat.st_uid);
	gr = getgrgid(mystat.st_gid);
	iaccess = mystat.st_mode;
	iaccess = itoo(iaccess);
	type_file_l(mystat);
	write_access(iaccess % 1000 / 100);
	write_access(iaccess % 100 / 10);
	write_access(iaccess % 10);
	ft_putstr("  ");
	a = count_num(t.count_lnk);
	while (a-- > count_num(mystat.st_nlink))
		ft_putstr(" ");
	ft_putnbr(mystat.st_nlink);
	ft_putstr(" ");
	ft_putstr(pw->pw_name);
	ft_putstr("  ");
	ft_putstr(gr->gr_name);
	omegalul_l(mystat, t);
}
