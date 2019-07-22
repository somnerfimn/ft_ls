/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 05:53:48 by oorlov            #+#    #+#             */
/*   Updated: 2019/06/20 05:53:49 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void						fork_key(t_file_time *fid, t_keycheck btw, int c)
{
	int						count;

	count = 0;
	if (btw.r == 0)
		while (count != c)
			ft_ls(fid[count++], btw);
	if (btw.r == 1)
	{
		count = c - 1;
		while (count != -1)
			ft_ls(fid[count--], btw);
	}
}

int							check_slnk(char *arg)
{
	DIR						*mydir;
	struct dirent			*myf;
	struct stat				mystat;
	char					*fn;
	int						result;

	result = 0;
	dir_p(arg) ? mydir = opendir(dir_p(arg)) : exit(1);
	if (mydir != NULL)
	{
		while ((myf = readdir(mydir)) != NULL)
		{
			fn = (char *)malloc(ft_strlen(arg) + ft_strlen(myf->d_name) + 2);
			add_dir_piece(arg, fn, myf);
			lstat(arg, &mystat);
			if (arg[ft_strlen(arg) - 1] != '/')
				if (S_ISLNK(mystat.st_mode))
					result = 1;
			free(fn);
		}
		closedir(mydir);
	}
	return (result);
}

void						open_all(int count, char **arg, t_keycheck btw)
{
	int						c;
	int						b;
	int						check;
	t_file_time				*fid;

	c = -1;
	while (++c < count - 1)
	{
		check = check_slnk(arg[c]);
		fid = (t_file_time *)malloc(sizeof(t_file_time) * count_files(arg[c]));
		(!fid) ? perror("fid") : 0;
		if (count > 2 && count_files(arg[c]) != 0)
			print_double_point(arg[c]);
		b = files_struct(arg[c], fid, btw);
		sort_files_time(fid, count_files(arg[c]));
		btw.t == 0 ? sort_files_ascii(fid, count_files(arg[c])) : 0;
		if (check == 0)
		{
			fork_key(fid, btw, b);
			(c < count - 2 && b != 0) ? ft_putstr("\n") : 0;
			if (btw.r_large == 1)
				btw.a == 0 ? recursion(arg[c], btw) : a_recursion(arg[c], btw);
		}
		free(fid);
	}
}

void						open_once(char *arg, t_keycheck btw)
{
	int						count_file;
	t_file_time				*fid;

	count_file = 0;
	fid = (t_file_time *)malloc(sizeof(t_file_time) * count_files(arg));
	(!fid) ? perror("fid") : 0;
	count_file = files_struct(arg, fid, btw);
	btw.t == 0 ? sort_files_ascii(fid, count_files(arg)) :
		sort_files_time(fid, count_files(arg));
	fork_key(fid, btw, count_file);
	if (btw.r_large == 1)
		btw.a == 0 ? recursion(arg, btw) : a_recursion(arg, btw);
	free(fid);
}
