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
	while (arg[count] != 0)
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
		if (arg[tmp] == dst[count] && arg[tmp])
			return (0);
	}
	return (-1);
}

char						*dir_piece(char *arg)
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
		return(".");
	result[count] = '\0';
	return (result);
}

void						search_file(int argc, char **copy_argv, t_keycheck btw)
{
	DIR						*mydir;
	struct dirent			*myf;
	struct stat				mystat;
	int						count;
	char					*fn;

	count = 0;
	while (count != argc - 1)
	{
		mydir = opendir(dir_piece(copy_argv[count]));
		if (mydir != NULL)
		{
			while ((myf = readdir(mydir)) != NULL)
			{
				fn = (char *)malloc(ft_strlen(copy_argv[count]) + ft_strlen(myf->d_name) + 2);
				ft_strcpy(fn, copy_argv[count]);
				ft_strcpy(fn + ft_strlen(copy_argv[count]), "/");
				ft_strcpy(fn + ft_strlen(copy_argv[count]) + 1, myf->d_name);
				lstat(copy_argv[count], &mystat);
				if (muhi_otdelno(copy_argv[count], myf->d_name) == 0)
					if (!(S_ISDIR(mystat.st_mode)))
					{
						btw.l == 1 ? access_rights(mystat) : 0;
						ft_putendl(copy_argv[count]);
					}
				free(fn);
			}
			closedir(mydir);
		}
		count++;
	}
}
