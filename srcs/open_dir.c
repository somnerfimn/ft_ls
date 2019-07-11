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
	printf("123\n");
	if (mydir != NULL)
	{
		while ((myf = readdir(mydir)) != NULL)
		{
			fn = (char *)malloc(ft_strlen(dir_n) + ft_strlen(myf->d_name) + 2);
			ft_strcpy(fn, dir_n);
			ft_strcpy(fn + ft_strlen(dir_n), "/");
			ft_strcpy(fn + ft_strlen(dir_n) + 1, myf->d_name);
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
		closedir (mydir);
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
			fn = (char *)malloc(ft_strlen(dir_n) + ft_strlen(myf->d_name) + 2);
			ft_strcpy(fn, dir_n);
			ft_strcpy(fn + ft_strlen(dir_n), "/");
			ft_strcpy(fn + ft_strlen(dir_n) + 1, myf->d_name);
			lstat(fn, &mystat);
			if (S_ISDIR(mystat.st_mode) && myf->d_name[1] != '\0')
				if (ft_strcmp(myf->d_name, "..") != 0)
				{
					ft_putstr("\n");
					ft_putstr(fn);
					ft_putstr(":\n");
					open_once(fn, btw);
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

int							block_size(struct stat mystat)
{
	int						bsize;
	int						tmp;

	bsize = 0;
	tmp = 0;
	tmp += mystat.st_size;
	bsize = tmp / 4096;
	bsize *= 8;
	bsize += 8;
	if (mystat.st_size == 0)
		return (0);
	return (bsize);
}

t_file_time					link_name(t_file_time fid, char *fn)
{
	char					*linkbuf;
	int						len;
	int						i;

	i = 0;
	linkbuf = (char *)malloc(sizeof(char) * 4096);
	fid.lnk = (char *)malloc(sizeof(char) * 4096);
	len = readlink(fn, linkbuf, sizeof(linkbuf));
	linkbuf[len] = '\0';
	fid.lnk = ft_strcpy(fid.lnk, linkbuf);
	free(linkbuf);
	len = 0;
	return(fid);
}

int							files_struct(char *dir_n, t_file_time *fid, t_keycheck btw)
{
	DIR						*mydir;
	int						bsize;
	struct dirent			*myf;
	struct stat				mystat;
	int						count;
	char					*fn;

	count = 0;
	bsize = 0;
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
			ft_putendl(fid[count].lnk);
			bsize += block_size(mystat);
			if ((btw.a == 0 && myf->d_name[0] == '.') || S_ISDIR(mystat.st_mode))
				bsize -= block_size(mystat);
			fid[count].mystat = mystat;
			if (S_ISLNK(mystat.st_mode))
				fid[count] = link_name(fid[count], fn);
			count++;
			free(fn);
		}
		closedir(mydir);
		if (btw.l == 1)
		{
			ft_putstr("total ");
			ft_putnbr(bsize);
			ft_putstr("\n");
		}
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
		if (count > 2 && count_files(arg[c]) != 0)
		{
			ft_putstr(arg[c]);
			ft_putstr(":\n");
		}
		b = files_struct(arg[c], fid, btw);
		sort_files_time(fid, count_files(arg[c]));
		if (btw.t == 0)
			sort_files_ascii(fid, count_files(arg[c]));
		fork_key(fid, btw, b);
		c++;
		if (c < count - 1 && b != 0)
			ft_putstr("\n");
		free(fid);
		if (btw.r_large == 1 && btw.a == 0)
			recursion(arg[c], btw);
		if (btw.r_large == 1 && btw.a == 1)
			a_recursion(arg[c], btw);
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
	count_file = files_struct(arg, fid, btw);
	if (btw.t == 0)
		sort_files_ascii(fid, count_files(arg));
	else
		sort_files_time(fid, count_files(arg));
	fork_key(fid, btw, count_file);
	free(fid);
	if (btw.r_large == 1 && btw.a == 0)
		recursion(arg, btw);
	if (btw.r_large == 1 && btw.a == 1)
		a_recursion(arg, btw);
}
