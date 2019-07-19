/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subf2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 02:33:39 by oorlov            #+#    #+#             */
/*   Updated: 2019/07/14 02:33:41 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void		add_dir_piece(char *dir_n, char *fn, struct dirent *myf)
{
		ft_strcpy(fn, dir_n);
		ft_strcpy(fn + ft_strlen(dir_n), "/");
		ft_strcpy(fn + ft_strlen(dir_n) + 1, myf->d_name);
}

void		print_double_point(char *name)
{
	ft_putstr(name);
	ft_putstr(":\n");
}

void		print_total(int bsize)
{
	ft_putstr("total ");
	ft_putnbr(bsize);
	ft_putstr("\n");
}

void		print_err_dir(char *err_dir, int tmp, struct stat mystat)
{
	
	if (tmp == 1)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(err_dir);
		ft_putstr(": No such file or directory\n");
	}
	else if (tmp == 2 && !(S_ISDIR(mystat.st_mode)))
	{
		ft_putstr("ft_ls: ");
		ft_putstr(err_dir);
		ft_putstr(": Not a directory\n");
	}
}

void		print_nap(char *name, t_keycheck btw)
{
	char	*linkbuf;
	int		len;

	linkbuf = (char *)malloc(sizeof(char) * 4096);
	len = readlink(name, linkbuf, sizeof(linkbuf));
	linkbuf[len] = '\0';
	ft_putstr(name);
	if (btw.l == 1)
	{
		ft_putstr(" -> ");
		ft_putstr(linkbuf);
	}
	ft_putstr("\n");
	free(linkbuf);
	linkbuf = NULL;
}