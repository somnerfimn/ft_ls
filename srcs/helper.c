/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:22:33 by oorlov            #+#    #+#             */
/*   Updated: 2019/07/08 15:22:38 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int			main(int argc, char **argv)
{
	int		count;	
	int		tmp;

	count = 1;
	tmp = 1;
	while (argv[1][count] != '\0')
	{
		if (argv[1][count] == '/' && argv[1][count + 1] != '\0')
			tmp = count + 1;
		count++;
	}
	printf("%c", argv[1][tmp]);
	printf("%c", argv[1][tmp + 1]);
	printf("%c", argv[1][tmp + 2]);
	printf("%c", argv[1][tmp + 3]);
	printf("%c\n", argv[1][tmp + 4]);
}
