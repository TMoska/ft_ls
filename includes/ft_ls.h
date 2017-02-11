/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:31:34 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/11 19:59:56 by tmoska           ###   ########.fr       */
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
# include <sys/acl.h>

# define BUFF 256
# define SIX_MONTHS_SECONDS 16000000

# ifdef __APPLE__
#  define MULTIOS_TIME(x) (x->st_mtimespec.tv_sec)
# else
#  define MULTIOS_TIME(x) (x->st_mtime)
# endif

typedef char		t_bool;
typedef struct stat	t_stat;

typedef struct		s_listing
{
	t_bool			recursive;
	t_bool			recursing;
	t_bool			all;
	t_bool			long_format;
	t_bool			sort_reverse;
	t_bool			sort_time_modified;
	t_bool			should_print_dir_names;
	t_bool			printed_something_already;
	t_bool			handle_singles;
	t_bool			handling_singles;
	t_bool			cap_a;
	t_bool			o;
	t_bool			g;
	t_bool			d;
	t_bool			one;
	int				recursive_depth;
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
void				no_such_file_or_dir(char *folder_name, t_listing *listing, \
		t_list **directories);
void				exit_if_arg_empty(char *arg);
void				do_directories(t_list *arg, t_list *directory,\
		t_listing *listing);
void				print_folder(char *folder_name, t_listing *listing);
void				do_single_directory(char *folder_name, t_list *directory,\
		t_listing *listing);
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
int					do_print_folder(char *folder_name, t_listing *listing);
int					handle_bonus(char c, t_listing *listing);
void				reverse_lists_if_needed(t_list **arggs, \
	t_list **file_list, t_list **dir_list, t_listing *listing);
void				del_file(t_file *file);
void				deep_del_files(t_list **lst);
void				del_files_n_fullnames(void **list_content, \
		size_t *content_size);
int					is_a_dot_file(char *folder_name);
void				del_deep_char(char **arr);
int					link_will_loop(char ***split_link, char ***split_path,\
		char link[BUFF], int i);
void				clean_listing(t_list *dir_list, t_list *file_list);
#endif
