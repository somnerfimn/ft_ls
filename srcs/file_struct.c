/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 00:34:59 by oorlov            #+#    #+#             */
/*   Updated: 2019/07/22 00:35:01 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_file_time				link_name(t_file_time fid, char *fn)
{
	char				*linkbuf;
	int					len;
	int					i;

	i = 0;
	linkbuf = (char *)malloc(sizeof(char) * 4096);
	fid.lnk = (char *)malloc(sizeof(char) * 4096);
	len = readlink(fn, linkbuf, sizeof(linkbuf));
	linkbuf[len] = '\0';
	fid.lnk = ft_strcpy(fid.lnk, linkbuf);
	free(linkbuf);
	len = 0;
	return (fid);
}

int						block_size(struct stat ms, t_keycheck btw, char *n)
{
	int					bsize;
	int					tmp;

	bsize = 0;
	tmp = 0;
	tmp += ms.st_blocks;
	bsize = tmp;
	if (ms.st_size == 0 || S_ISDIR(ms.st_mode))
		return (0);
	if (btw.a == 0 && n[0] == '.')
		return (0);
	return (bsize);
}

t_fstr					defined(void)
{
	t_fstr				t;

	t.bsize = 0;
	t.count = 0;
	return (t);
}

int						files_struct(char *dir_n,
	t_file_time *fid, t_keycheck btw)
{
	DIR					*mydir;
	struct dirent		*myf;
	struct stat			mystat;
	t_fstr				t;

	t = defined();
	mydir = opendir(dir_n);
	if (mydir != NULL)
	{
		while ((myf = readdir(mydir)) != NULL)
		{
			t.fn = (char *)malloc(ft_mall(dir_n, myf->d_name));
			add_dir_piece(dir_n, t.fn, myf);
			fid[t.count].myfile = myf;
			lstat(t.fn, &mystat);
			t.bsize += block_size(mystat, btw, myf->d_name);
			fid[t.count++].mystat = mystat;
			if (S_ISLNK(mystat.st_mode))
				fid[t.count - 1] = link_name(fid[t.count - 1], t.fn);
			free(t.fn);
		}
		closedir(mydir);
		(btw.l == 1 && check_slnk(dir_n) == 0) ? print_total(t.bsize) : 0;
	}
	return (t.count);
}
