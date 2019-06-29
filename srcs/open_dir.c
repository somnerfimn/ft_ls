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
			fn = (char *)malloc(ft_strlen(dir_n) + ft_strlen(myf->d_name) + 2);
			ft_strcpy(fn, dir_n);
			ft_strcpy(fn + ft_strlen(dir_n), "/");
			ft_strcpy(fn + ft_strlen(dir_n) + 1, myf->d_name);
			lstat(fn, &mystat);
			if (S_ISDIR(mystat.st_mode) && ft_strcmp(".", myf->d_name) != 0 &&
				ft_strcmp("..", myf->d_name) != 0 && ft_strcmp(".git", myf->d_name) != 0)
			{
				ft_putstr("\n");
				ft_putstr(fn);
				ft_putstr(":\n");
				open_once(myf->d_name, btw);
			}
			free(fn);
		}
		closedir (mydir);
	}
}

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

int							files_struct(char *dir_n, t_file_time *fid)
{
	DIR						*mydir;
	struct dirent			*myf;
	struct stat				mystat;
	int						count;
	char					*fn;

	count = 0;
	mydir = opendir(dir_n);
	if (mydir != NULL)
	{
		while ((myf = readdir(mydir)) != NULL)
		{
			fn = (char *)malloc(ft_strlen(dir_n) + ft_strlen(myf->d_name) + 2);
			ft_strcpy(fn, dir_n);
			ft_strcpy(fn + ft_strlen(dir_n), "/");
			ft_strcpy(fn + ft_strlen(dir_n) + 1, myf->d_name);
			fid[count].myfile = myf;
			lstat(fn, &mystat);
			fid[count].mystat = mystat;
			count++;
			free(fn);
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
		fid = (t_file_time *)malloc(sizeof(t_file_time) * count_files(arg[c]));
		if (!fid)
			perror("fid");
		b = files_struct(arg[c], fid);
		if (count > 2 && b != 0)
		{
			ft_putstr(arg[c]);
			ft_putstr(":\n");
		}
		sort_files_time(fid, count_files(arg[c]));
		if (btw.t == 0)
			sort_files_ascii(fid, count_files(arg[c]));
		fork_key(fid, btw, b);
		c++;
		if (c < count - 1 && b != 0)
			ft_putstr("\n");
		free(fid);
		if (btw.r_large == 1)
			recursion(arg[c], btw);
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
	if (btw.r_large == 1)
		recursion(arg, btw);
}
