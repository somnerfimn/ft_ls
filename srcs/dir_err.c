/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 23:16:08 by oorlov            #+#    #+#             */
/*   Updated: 2019/07/21 23:16:09 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int					ft_mall(char *name, char *d_name)
{
	int				len;
	int				len_d;

	len = ft_strlen(name);
	len_d = ft_strlen(d_name);
	return (len + len_d + 2);
}

void				dir_err(int argc, char **copy_argv)
{
	DIR						*mydir;
	struct dirent			*myf;
	struct stat				mystat;
	t_dir_err				a;

	a.count = -1;
	a.tmp = 1;
	while (++a.count != argc - 1)
	{
		a.pdir = dir_p(copy_argv[a.count]);
		mydir = opendir(a.pdir);
		if (mydir != NULL)
		{
			while ((myf = readdir(mydir)) != NULL && a.tmp == 1)
			{
				a.fn = (char *)malloc(ft_mall(copy_argv[a.count], myf->d_name));
				add_dir_piece(copy_argv[a.count], a.fn, myf);
				lstat(copy_argv[a.count], &mystat);
				a.tmp = muhi_otdelno(copy_argv[a.count], myf->d_name);
				free(a.fn);
			}
			closedir(mydir);
		}
		a.tmp > 0 ? print_err_dir(copy_argv[a.count], a.tmp, mystat) : 0;
	}
}
