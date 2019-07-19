/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:33:57 by oorlov            #+#    #+#             */
/*   Updated: 2019/06/10 15:33:58 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int					count_key(int argc, char **argv)
{
	int				result;

	result = 1;
	while (result != argc)
		if (argv[result][0] == '-' && argv[result][1] != '\0')
			result++;
		else
			return (result - 1);
	return (result - 1);
}

int					count_files(char *dir_name)
{
	DIR				*mydir;
	struct dirent	*myfile;
	int				result;

	result = 0;
	mydir = opendir(dir_name);
	if (mydir != NULL)
	{
		while ((myfile = readdir(mydir)) != NULL)
			result++;
		closedir(mydir);
	}
	return (result);
}

void				print_err(char key_err)
{
	ft_putstr("ft_ls: illegal option -- ");
	write(1, &key_err, 1);
	ft_putendl("\nusage: ft_ls [-Ralrt] [file ...]");
	exit (1);
}

int					check_some_key(char *arg, char key)
{
	int				count;

	count = 1;
	while (arg[count])
	{
		if (arg[count] != 'l' && arg[count] != 'a' && arg[count] != 'r' &&
			arg[count] != 't' && arg[count] != 'R')
			print_err(arg[count]);
		if (arg[count] == key)
			return (1);
		count++;
	}
	return (0);
}

t_keycheck			search_key(int argc, char **arguments, t_keycheck btw)
{
	int				count;

	count = 1;
	while (count <= argc)
	{
		if (arguments[count][0] == '-')
		{
			if (check_some_key(arguments[count], 'a') == 1)
				btw.a = 1;
			if (check_some_key(arguments[count], 't') == 1)
				btw.t = 1;
			if (check_some_key(arguments[count], 'r') == 1)
				btw.r = 1;
			if (check_some_key(arguments[count], 'l') == 1)
				btw.l = 1;
			if (check_some_key(arguments[count], 'R') == 1)
				btw.r_large = 1;
		}
		count++;
	}
	return (btw);
}

void				dir_err(int argc, char **copy_argv)
{
	DIR						*mydir;
	struct dirent			*myf;
	struct stat				mystat;
	int						count;
	char					*fn;
	char					*dir;
	int						tmp;

	count = -1;
	tmp = 1;
	while (++count != argc - 1)
	{
		dir = dir_p(copy_argv[count]);
		dir ? mydir = opendir(dir) : exit(1);
		if (mydir != NULL)
		{
			while ((myf = readdir(mydir)) != NULL && tmp == 1)
			{
				fn = (char *)malloc(ft_strlen(copy_argv[count]) + ft_strlen(myf->d_name) + 2);
				add_dir_piece(copy_argv[count], fn, myf);
				lstat(copy_argv[count], &mystat);
				muhi_otdelno(copy_argv[count], myf->d_name) == 0 ? tmp = 0 : 1;
				muhi_otdelno(copy_argv[count], myf->d_name) == 2 ? tmp = 2 : 1;
				free(fn);
			}
			closedir(mydir);
		}
		if (tmp > 0)
			print_err_dir(copy_argv[count], tmp, mystat);
	}
}
