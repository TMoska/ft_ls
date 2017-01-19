/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:59:22 by moska             #+#    #+#             */
/*   Updated: 2017/01/19 05:16:13 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			is_a_valid_file(char *folder_name)
{
	DIR				*dir;
	struct dirent	*read;
	char			*path;
	char			*short_name;
	int				ret;

	ret = 0;
	path = ft_get_path(folder_name);
	short_name = ft_basename(folder_name);
	dir = opendir(path);
	while ((read = readdir(dir)))
		if (ft_strequ(short_name, read->d_name))
			ret = 1;
	free(path);
	closedir(dir);
	return (ret);
}

static void			read_directory(char *folder_name, t_list **directories,
		t_list **file_list)
{
	DIR				*opened;
	t_list			*files;
	struct dirent	*read;

	files = NULL;
	if ((opened = opendir(folder_name)))
	{
		while ((read = readdir(opened)))
			ft_lst_push_front(&files, ft_strdup(read->d_name));
		ft_lst_push_back(directories, files);
		closedir(opened);
	}
	else
	{
		ft_lst_push_back(directories, NULL);
		if (errno == ENOTDIR && is_a_valid_file(folder_name))
			ft_lst_push_front(file_list, folder_name);
		else
			no_such_file_or_dir(folder_name);
	}
}

static t_bool		link_is_a_file(char *name, t_list **arguments,
		t_list *arg, t_listing *listing)
{
	t_stat			stats;
	DIR				*opened;

	if (*(ft_strchr(name, '\0') - 1) == '/')
		return (0);
	if (lstat(name, &stats))
		ft_lst_removenode(arguments, arg);
	else if (S_ISLNK(stats.st_mode))
	{
		if ((opened = opendir(name)))
		{
			closedir(opened);
			return (listing->long_format);
		}
		return (1);
	}
	return (0);
}

static void			setup(t_list **directories, t_list **file_list \
							, t_list **arguments, t_list **arg)
{
	ft_lstsort(arguments, &ft_strcmp);
	*directories = NULL;
	*file_list = NULL;
	*arg = *arguments;
}

void				start_listing(t_list **arguments, t_listing *listing)
{
	t_list			*directories;
	t_list			*file_list;
	t_list			*arg;
	char			*folder_name;

	setup(&directories, &file_list, arguments, &arg);
	while (arg)
	{
		folder_name = (char*)arg->content;
		if (listing->should_handle_screwups \
				&& link_is_a_file(folder_name, arguments, arg, listing))
			ft_lst_push_back(&file_list, folder_name);
		else
			read_directory(folder_name, &directories, &file_list);
		arg = arg->next;
	}
	if (listing->sort_reverse)
	{
		ft_lstrev(arguments);
		ft_lstrev(&file_list);
		ft_lstrev(&directories);
	}
	if (listing->dir_as_files)
		print_file_list(*arguments, arguments, listing);
	print_files_and_directories(arguments, &directories, &file_list, listing);
}
