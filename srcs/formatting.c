/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:07:06 by moska             #+#    #+#             */
/*   Updated: 2017/01/19 02:59:49 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		get_file_type(t_file *file)
{
	if (file->is_symlink)
		return ('l');
	if (S_ISBLK(file->stat->st_mode))
		return ('b');
	else if (file->stat->st_mode & S_IFCHR)
		return ('c');
	else if (S_ISSOCK(file->stat->st_mode))
		return ('s');
	else if (file->stat->st_mode & S_IFIFO)
		return ('p');
	else if (file->stat->st_mode & S_IFDIR)
		return ('d');
	return ('-');
}

static int		get_size_string_length(t_file *file, uintmax_t *largest_major)
{
	uintmax_t		minor;
	uintmax_t		major;
	int				total;

	file->file_type = get_file_type(file);
	if (file->file_type == 'b' || file->file_type == 'c')
	{
		major = major(file->stat->st_rdev);
		minor = minor(file->stat->st_rdev);
		replace_if_greater(largest_major, major);
		file->file_size_first = ft_itoa_ularge(major);
		file->file_size_second = ft_itoa_ularge(minor);
		total = ft_strlen(file->file_size_first)
			+ ft_strlen(file->file_size_second) + 2;
		return (total);
	}
	else
	{
		file->file_size_second = ft_itoa_ularge(lstat_or_stat(file)->st_size);
		return (ft_strlen(file->file_size_second));
	}
}

void			formatting(t_strlens *strlens, t_list *dir_files,\
		t_listing *listing)
{
	t_file		*file;
	uintmax_t	largest_nlink;
	uintmax_t	largest_major;

	ft_bzero(strlens, sizeof(t_strlens));
	largest_nlink = 0;
	largest_major = 0;
	while (dir_files && (file = (t_file*)dir_files->content))
	{
		if (!should_print_entry(file, listing))
		{
			dir_files = dir_files->next;
			continue ;
		}
		replace_if_greater(&largest_nlink, lstat_or_stat(file)->st_nlink);
		replace_if_greater_int(&strlens->file_size,\
				get_size_string_length(file, &largest_major));
		replace_group(strlens, file);
		replace_owner(strlens, file);
		dir_files = dir_files->next;
	}
	strlens->nlink = ft_count_umax_digits(largest_nlink);
}
