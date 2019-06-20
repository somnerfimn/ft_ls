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

int							files_struct(char *dir_name, t_file_time *fid)
{
	DIR						*mydir;
	struct dirent			*myfile;
	struct stat				mystat;
	int						count;

	count = 0;
	mydir = opendir(dir_name);
	if (mydir != NULL)
	{
		while ((myfile = readdir(mydir)) != NULL)
		{
			fid[count].myfile = myfile;
			lstat(myfile->d_name, &mystat);
			fid[count].mystat = mystat;
			count++;
		}
		closedir(mydir);
	}
	return (count);
}

void						open_all(int count, char **arg, t_keycheck btw)
{
	int						c;
	int						b;
	t_file_time				*fid;

	c = 0;
	b = 0;
	while (c < count - 1)
	{
		if (count > 2)
		{
			ft_putstr(arg[c]);
			ft_putstr(":\n");
		}
		fid = (t_file_time *)malloc(sizeof(t_file_time) * count_files(arg[c]));
		if (!fid)
			perror("fid");
		b = files_struct(arg[c], fid);
		sort_files_time(fid, count_files(arg[c]));
		if (btw.t == 0)
			sort_files_ascii(fid, count_files(arg[c]));
		fork_key(fid, btw, b);
		c++;
		if (c < count - 1)
			ft_putstr("\n");
		free(fid);
	}
}

void						open_once(char *arg, t_keycheck btw)
{
	int						count_file;
	t_file_time				*fid;

	count_file = 0;
	fid = (t_file_time *)malloc(sizeof(t_file_time) * count_files(arg));
	if (!fid)
		perror("fid");
	count_file = files_struct(arg, fid);
	if (btw.t == 0)
		sort_files_ascii(fid, count_files(arg));
	else
		sort_files_time(fid, count_files(arg));
	fork_key(fid, btw, count_file);
	free(fid);
	fid = NULL;
}
