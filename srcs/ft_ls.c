/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 01:28:48 by oorlov            #+#    #+#             */
/*   Updated: 2019/05/19 01:28:49 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int						ft_strlen(const char *str)
{
	size_t					tmp;

	tmp = 0;
	while (str[tmp] != '\0')
		tmp++;
	return (tmp);
}

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	count;

	count = 0;
	str = (char *)malloc(sizeof(*str) * (size + 1));
	if (!str)
		return (NULL);
	while (count < size + 1)
		str[count++] = '\0';
	return (str);
}

void						write_path_lnk(t_file_time file_in_dir, t_keycheck btw)
{
	char					linkbuf[4096];
	int						len;

	if (btw.l == 1)
	{
		len = readlink(file_in_dir.myfile->d_name, linkbuf, sizeof(linkbuf));
		linkbuf[len] = '\0';
		ft_putstr(" -> ");
		ft_putendl(linkbuf);
	}
	else
		ft_putstr("\n");
}

void						ft_ls(t_file_time file_in_dir, t_keycheck btw)
{
	if (btw.a == 0)
		if (file_in_dir.myfile->d_name[0] != '.')
		{
			if (btw.l == 1)
				access_rights(file_in_dir.mystat);
			ft_putstr(file_in_dir.myfile->d_name);
			if (S_ISLNK(file_in_dir.mystat.st_mode))
				write_path_lnk(file_in_dir, btw);
			else
				ft_putstr("\n");
		}
	if (btw.a == 1)
	{
		if (btw.l == 1)
			access_rights(file_in_dir.mystat);
		ft_putstr(file_in_dir.myfile->d_name);
		if (S_ISLNK(file_in_dir.mystat.st_mode))
			write_path_lnk(file_in_dir, btw);
		else
			ft_putstr("\n");
	}
}

int							main(int argc, char **argv)
{
	char					*copy_argv[argc - 1 - count_key(argc, argv)];
	int						count;
	t_keycheck				btw;

	btw.a = 0;
	btw.l = 0;
	btw.t = 0;
	btw.r = 0;
	btw.r_large = 0;
	count = 0;
	btw = search_key(count_key(argc, argv), argv, btw);
	if (count_key(argc, argv) + 1 == argc)
		open_once(".", btw);
	else
	{
		while (++count != argc - count_key(argc, argv))
			copy_argv[count - 1] = argv[count + count_key(argc, argv)];
		sort_params(argc - count_key(argc, argv) - 1, copy_argv);
		dir_err(argc - count_key(argc, argv), copy_argv);
		open_all(argc - count_key(argc, argv), copy_argv, btw);
	}
	//system("leaks ft_ls");
}
