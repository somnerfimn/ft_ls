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
	exit(1);
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
