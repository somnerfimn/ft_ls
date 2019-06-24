/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:33:27 by oorlov            #+#    #+#             */
/*   Updated: 2019/06/12 12:33:28 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char						*ft_strcpy(char *dst, const char *src)
{
	int						count;

	count = 0;
	while (src[count] != '\0')
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
	return (dst);
}

t_file_time					*sort_files_time(t_file_time *af, int files_count)
{
	t_file_time				tmp;
	int						count;
	int						find;

	find = 1;
	while (find)
	{
		find = 0;
		count = 0;
		while (count < files_count - 1)
		{
			if ((af[count].mystat.st_mtime - af[count + 1].mystat.st_mtime) < 0)
			{
				tmp = af[count];
				af[count] = af[count + 1];
				af[count + 1] = tmp;
				find = 1;
			}
			count++;
		}
	}
	return (af);
}

t_file_time					*sort_files_ascii(t_file_time *af, int files_count)
{
	t_file_time				tmp;
	int						c;
	int						find;

	find = 1;
	while (find)
	{
		find = 0;
		c = 0;
		while (c < files_count - 1)
		{
			if (ft_strcmp(af[c].myfile->d_name, af[c + 1].myfile->d_name) > 0)
			{
				tmp = af[c];
				af[c] = af[c + 1];
				af[c + 1] = tmp;
				find = 1;
			}
			c++;
		}
	}
	return (af);
}

void						sort_params(int argc, char **copy_argv)
{
	char					*tmp;
	int						count;
	int						find;

	find = 1;
	while (find)
	{
		find = 0;
		count = 0;
		while (count < argc - 1)
		{
			if (ft_strcmp(copy_argv[count], copy_argv[count + 1]) > 0)
			{
				tmp = copy_argv[count];
				copy_argv[count] = copy_argv[count + 1];
				copy_argv[count + 1] = tmp;
				find = 1;
			}
			count++;
		}
	}
}
