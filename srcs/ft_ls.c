/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 01:28:48 by oorlov            #+#    #+#             */
/*   Updated: 2019/05/19 01:28:49 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void			write_path_lnk(t_file_time fid, t_keycheck btw)
{
	if (btw.l == 1)
	{
		ft_putstr(" -> ");
		ft_putendl(fid.lnk);
	}
	else
		ft_putstr("\n");
	free(fid.lnk);
}

void			ft_ls(t_file_time fid, t_keycheck btw, t_print t)
{
	if (btw.a == 0)
		if (fid.myfile->d_name[0] != '.')
		{
			if (btw.l == 1)
				access_rights(fid.mystat, t);
			ft_putstr(fid.myfile->d_name);
			if (S_ISLNK(fid.mystat.st_mode))
				write_path_lnk(fid, btw);
			else
				ft_putstr("\n");
		}
	if (btw.a == 1)
	{
		if (btw.l == 1)
			access_rights(fid.mystat, t);
		ft_putstr(fid.myfile->d_name);
		if (S_ISLNK(fid.mystat.st_mode))
			write_path_lnk(fid, btw);
		else
			ft_putstr("\n");
	}
}

void			manipulate(int ar, char **argv, char **c_argv, t_keycheck btw)
{
	sort_params(ar - count_key(ar, argv) - 1, c_argv);
	dir_err(ar - count_key(ar, argv), c_argv);
	search_file(ar - count_key(ar, argv), c_argv, btw);
	open_all(ar - count_key(ar, argv), c_argv, btw);
}

int				main(int argc, char **argv)
{
	char		*copy_argv[argc - 1 - count_key(argc, argv)];
	int			count;
	t_keycheck	btw;

	btw.a = 0;
	btw.l = 0;
	btw.t = 0;
	btw.r = 0;
	btw.r_large = 0;
	count = 0;
	btw = search_key(count_key(argc, argv), argv, btw);
	if (count_key(argc, argv) + 1 == argc)
		open_once(".", btw);
	else
	{
		while (++count != argc - count_key(argc, argv))
			copy_argv[count - 1] = argv[count + count_key(argc, argv)];
		manipulate(argc, argv, copy_argv, btw);
	}
}
