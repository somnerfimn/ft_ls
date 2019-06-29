/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:16:29 by oorlov            #+#    #+#             */
/*   Updated: 2019/06/24 13:16:30 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

// void				recursion(char *dir_n, t_keycheck btw)
// {
// 	DIR				*mydir;
// 	struct stat		mystat;
// 	struct dirent	myf;
// 	char			*fn;

// 	mydir = opendir(dir_n);
// 	if (mydir != NULL)
// 	{
// 		while ((myf = readdir(mydir)) != NULL)
// 		{
// 			fn = (char *)malloc(ft_strlen(dir_n) + ft_strlen(myf->d_name) + 2);
// 			ft_strcpy(fn, dir_n);
// 			ft_strcpy(fn + ft_strlen(dir_n), "/");
// 			ft_strcpy(fn + ft_strlen(dir_n) + 1, myf->d_name);
// 			lstat(fn, &mystat);
// 			if (S_ISDIR(mystat.st_mode))
// 				open_once(fn, btw);
// 			free(fn);
// 		}
// 		closedir (mydir);
// 	}
// }
