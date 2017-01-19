/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:31:34 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/19 06:54:21 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>
# include <errno.h>
# include <time.h>
# include <unistd.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>

# define BUFF 256
# define SIX_MONTHS_SECONDS 15778500

typedef char		t_bool;
typedef struct stat	t_stat;

typedef struct		s_listing
{
	t_bool			one_per_line;
	t_bool			dir_as_files;
	t_bool			recursive;
	t_bool			recursing;
	t_bool			all;
	t_bool			long_format;
	t_bool			sort_reverse;
	t_bool			sort_time_modified;
	t_bool			should_print_dir_names;
	t_bool			printed_something_already;
	t_bool			should_handle_screwups;
	t_bool			handle_singles;
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

typedef	struct		s_strlens
{
	int				nlink;
	uintmax_t		owner;
	uintmax_t		group;
	int				major;
	int				file_size;
}					t_strlens;

void				start_listing(t_list **arguments, t_listing *listing);
void				no_such_file_or_dir(char *folder_name);
void				exit_if_arg_empty(char *arg);
void				do_directories(t_list *arg, t_list *directory,\
		t_listing *listing);
void				print_folder(char *folder_name, t_listing *listing);
void				do_single_directory(char *folder_name, t_list *directory,\
		t_bool should_print_folder, t_listing *listing);
t_file				*setup_file(char *folder_name, char *directory,\
		t_listing *listing);
void				sort_files(t_list **dir_files, t_listing *listing);
void				print_files(t_list *dir_files, t_listing *listing);
t_bool				should_print_entry(t_file *file, t_listing *listing);
void				print_list(t_list *begin_list);
void				formatting(t_strlens *strlens, t_list *dir_files,\
		t_listing *listing);
t_stat				*lstat_or_stat(t_file *file);
int					ft_count_umax_digits(uintmax_t number);
void				print_file_permissions(t_file *file);
void				print_files_and_directories(t_list **arguments, \
		t_list **directories,\
		t_list **file_list, t_listing *listing);
void				replace_group(t_strlens *strlens, t_file *file);
void				replace_owner(t_strlens *strlens, t_file *file);
void				replace_if_greater_int(int *replace_if, int new_value);
void				replace_if_greater(uintmax_t *old, uintmax_t new);
void				print_single_file(t_file *file, t_listing *listing,\
	t_strlens *strlens);
void				illegal_option(char c);
void				print_file_list(t_list *file_list, t_list **arguments,\
	t_listing *listing);

#endif
