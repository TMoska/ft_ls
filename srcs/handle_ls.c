/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:59:22 by moska             #+#    #+#             */
/*   Updated: 2017/01/15 23:50:08 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

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
		{
			printf("file: %s\n", read->d_name);
			ft_lst_push_front(&files, ft_strdup(read->d_name));
		}
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

static void			print_files_and_directories(t_list **arguments,
		t_list **directories, t_list **file_list, t_listing *listing)
{
	if (*file_list && listing->should_handle_screwups)
	{
		// print_file_list(arguments, file_list, listing)
		ft_lstdel(file_list, NULL); // Todo: Segfault
		listing->should_print_dir_names = 1; // Todo: might not be needed as we know there are more than 1 arguments
	}
	listing->should_handle_screwups = 0;
	if (directories)
		do_directories(*arguments, *directories, listing);
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
		opened = opendir(name);
		if (opened)
		{
			closedir(opened);
			return (listing->long_format); // Todo: ???
		}
		return (1);
	}
	return (0);
}

static void			setup(t_list **directories, t_list **file_list
							, t_list **arguments, t_list **arg)
{
	ft_lstsort(arguments, &ft_strcmp);
	*directories = NULL;
	*file_list = NULL;
	*arg = *arguments;
}

void				handle_ls(t_list **arguments, t_listing *listing)
{
	t_list			*directories;
	t_list			*file_list;
	t_list			*arg;
	char			*folder_name;

	setup(&directories, &file_list, arguments, &arg);
	while (arg)
	{
		folder_name = (char*)arg->content;
		if (listing->should_handle_screwups && link_is_a_file(folder_name, arguments, arg, listing))
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
	print_files_and_directories(arguments, &directories, &file_list, listing);
}
