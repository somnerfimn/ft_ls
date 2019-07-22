/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 00:30:52 by oorlov            #+#    #+#             */
/*   Updated: 2019/07/22 00:30:54 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void				recursion(char *dir_n, t_keycheck btw)
{
	DIR				*mydir;
	struct stat		mystat;
	struct dirent	*myf;
	char			*fn;

	mydir = opendir(dir_n);
	if (mydir != NULL)
	{
		while ((myf = readdir(mydir)) != NULL)
		{
			fn = (char *)malloc(ft_mall(dir_n, myf->d_name));
			add_dir_piece(dir_n, fn, myf);
			lstat(fn, &mystat);
			if (S_ISDIR(mystat.st_mode) && (myf->d_name[0] != '.'))
			{
				ft_putstr("\n");
				ft_putstr(fn);
				ft_putstr(":\n");
				open_once(fn, btw);
			}
			free(fn);
		}
		closedir(mydir);
	}
}

void				a_recursion(char *dir_n, t_keycheck btw)
{
	DIR				*mydir;
	struct stat		mystat;
	struct dirent	*myf;
	char			*fn;

	mydir = opendir(dir_n);
	if (mydir != NULL)
	{
		while ((myf = readdir(mydir)) != NULL)
		{
			fn = (char *)malloc(ft_mall(dir_n, myf->d_name));
			add_dir_piece(dir_n, fn, myf);
			lstat(fn, &mystat);
			if (S_ISDIR(mystat.st_mode) && ft_strcmp(myf->d_name, ".") != 0)
				if (ft_strcmp(myf->d_name, "..") != 0)
				{
					ft_putstr("\n");
					ft_putstr(fn);
					ft_putstr(":\n");
					open_once(fn, btw);
				}
			free(fn);
		}
		closedir(mydir);
	}
}
