/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oorlov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 12:35:45 by oorlov            #+#    #+#             */
/*   Updated: 2019/06/09 12:35:47 by oorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include <pwd.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <grp.h>
# include <time.h>
# include <string.h>

typedef struct			s_keycheck
{
	int					a;
	int					l;
	int					t;
	int					r;
	int					r_large;
}						t_keycheck;

typedef struct			s_file_time
{
	struct dirent		*myfile;
	struct stat			mystat;
	char				*link_name;
}						t_file_time;

void					ft_putchar(char c);

void					ft_putstr(char *str);

void					ft_putendl(char *s);

void					ft_putnbr(int n);

int						ft_strcmp(const char *s1, const char *s2);

void					type_file_l(struct stat mystat);

int						itoo(int decimal_n);

void					write_access(int num);

void					print_time(time_t time_m);

int						count_key(int argc, char **argv);

void					access_rights(struct stat mystat);

int						count_files(char *dir_name);

int						files_struct(char *d, t_file_time *f, t_keycheck b);

t_file_time				*sort_files_time(t_file_time *af, int files_count);

t_file_time				*sort_files_ascii(t_file_time *af, int files_count);

void					ft_ls(t_file_time file_in_dir, t_keycheck btw);

int						check_some_key(char *argument, char key);

t_keycheck				search_key(int argc, char **arguments, t_keycheck btw);

void					fork_key(t_file_time *fid, t_keycheck btw, int b);

void					open_all(int count, char **argument, t_keycheck btw);

void					dir_err(int count, char **argument);

void					sort_params(int argc, char **copy_argv);

void					open_once(char *argument, t_keycheck btw);

char					*ft_strjoin(char const *s1, char const *s2);

char					*ft_strcpy(char *dst, const char *src);

int						ft_strlen(const char *str);

void					recursion(char *dir_n, t_keycheck btw);

#endif
