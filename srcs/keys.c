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

int					check_some_key(char *argument, char key)
{
	int				count;

	count = 0;
	while (argument[count])
		if (argument[count++] == key)
			return (1);
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

void				dir_err(int count, char **argument)
{
	int				count_arg;
	DIR				*mydir;

	count_arg = 0;
	while (count_arg != count - 1)
	{
		mydir = opendir(argument[count_arg]);
		if (mydir == NULL)
		{
			ft_putstr("ft_ls: ");
			perror(argument[count_arg]);
		}
		else
			closedir(mydir);
		count_arg++;
	}
}
