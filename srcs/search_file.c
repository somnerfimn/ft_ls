/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:03:04 by oorlov            #+#    #+#             */
/*   Updated: 2019/07/06 18:03:05 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int							muhi_otdelno(char *arg, char *dst)
{
	int						count;
	int						tmp;

	tmp = 0;
	count = 0;
	while (arg[count] != '\0')
	{
		if (arg[count] == '/' && arg[count + 1] != '\0')
			tmp = count + 1;
		count++;
	}
	count = 0;
	while(arg[tmp] == dst[count])
	{
		tmp++;
		count++;
		if (arg[tmp] == dst[count] && dst[count] == '\0')
			return (0);
		if (arg[tmp] == '/' && dst[count] == '\0')
			return (2);
	}
		return (1);
}

char						*dir_p(char *arg)
{
	int						count;
	char					*result;
	int						tmp;

	count = 0;
	tmp = 0;
	result = (char *)malloc(sizeof(char) * 4096);
	result[0] = '.';
	while (arg[count] != 0)
	{
		if (arg[count] == '/' && arg[count + 1] != '\0')
			tmp = count;
		count++;
	}
	count = 0;
	if (tmp != 0)
		while(count != tmp)
		{
			result[count] = arg[count];
			count++;
		}
	else
	{
		free(result);
		return(".");
	}
	result[count] = '\0';
	return (result);
}

void						search_file(int argc, char **c_argv, t_keycheck btw)
{
	DIR						*mydir;
	struct dirent			*myf;
	struct stat				mystat;
	int						count;
	char					*fn;

	count = -1;
	while (++count != argc - 1)
	{
		dir_p(c_argv[count]) ? mydir = opendir(dir_p(c_argv[count])) : exit(1);
		if (mydir != NULL)
		{
			while ((myf = readdir(mydir)) != NULL)
			{
				fn = (char *)malloc(ft_strlen(c_argv[count]) + ft_strlen(myf->d_name) + 2);
				add_dir_piece(c_argv[count], fn, myf);
				lstat(c_argv[count], &mystat);
				if (muhi_otdelno(c_argv[count], myf->d_name) == 0)
				{
					if (!(S_ISDIR(mystat.st_mode)) && btw.l == 1)
						if (c_argv[count][ft_strlen(c_argv[count]) - 1] != '/')
							access_rights(mystat);
					S_ISDIR(mystat.st_mode) ? 1 : print_nap(c_argv[count], btw);
				}
				free(fn);
			}
			closedir(mydir);
		}
//		count++;
	}
}
