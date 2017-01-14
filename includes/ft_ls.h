/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:31:34 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/14 23:15:10 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
**	stdlib - exit
*/

# include "libft.h"
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>
# include <errno.h>

typedef char		t_bool;
typedef struct stat	t_stat;

typedef struct		s_listing
{
	t_bool			recursive;
	t_bool			all;
	t_bool			long_format;
	t_bool			sort_reverse;
	t_bool			sort_time_modified;
	t_bool			should_print_dir_names;
	t_bool			printed_folder_already;
}					t_listing;

typedef struct		s_file
{
	char			*basename;
	char			*full_name;
	t_stat			*stat;
	t_stat			*lstat;
	time_t			time_generated;
	char			file_type;
	char			*owner;
	char			*group;
	char			*file_size_first;
	char			*file_size_second;
	int				is_symlink;
}					t_file;

void				handle_ls(t_list **arguments, t_listing *listing);
void				no_such_file_or_dir(char *folder_name);
void				exit_if_arg_empty(char *arg);
void				do_directories(t_list *arg, t_list *directory,\
					t_listing *listing);
void				print_folder(char *folder_name, t_listing *listing);
void				do_single_directory(char *folder_name, t_list *directory, \
					t_bool should_print_folder, t_listing *listing);
t_file				*setup_file(char *folder_name, char *directory,\
					t_listing *listing);
#endif
