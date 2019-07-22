/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 22:59:05 by oorlov            #+#    #+#             */
/*   Updated: 2019/07/21 22:59:06 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int						ft_strlen(const char *str)
{
	size_t				tmp;

	tmp = 0;
	while (str[tmp] != '\0')
		tmp++;
	return (tmp);
}

char					*ft_strnew(size_t size)
{
	char				*str;
	size_t				count;

	count = 0;
	str = (char *)malloc(sizeof(*str) * (size + 1));
	if (!str)
		return (NULL);
	while (count < size + 1)
		str[count++] = '\0';
	return (str);
}

int						count_key(int argc, char **argv)
{
	int					result;

	result = 1;
	while (result != argc)
		if (argv[result][0] == '-' && argv[result][1] != '\0')
			result++;
		else
			return (result - 1);
	return (result - 1);
}
