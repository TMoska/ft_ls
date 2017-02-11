/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:59:22 by moska             #+#    #+#             */
/*   Updated: 2017/02/11 19:52:02 by tmoska           ###   ########.fr       */
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
	if (!(dir = opendir(path)))
	{
		free(path);
		return (0);
	}
	while ((read = readdir(dir)))
		if (ft_strequ(short_name, read->d_name))
			ret = 1;
	if (path)
		free(path);
	closedir(dir);
	return (ret);
}

static void			read_directory(char *folder_name, t_list **directories,
		t_list **file_list, t_listing *listing)
{
	DIR				*opened;
	t_list			*files;
	struct dirent	*read;

	files = NULL;
	if ((opened = opendir(folder_name)))
	{
		while ((read = readdir(opened)))
			ft_lstadd(&files, ft_lstnew(read->d_name, \
						ft_strlen(read->d_name) + 1));
		ft_lstadd_back(directories, ft_lstnew(files, sizeof(*files)));
		ft_memdel((void**)&files);
		closedir(opened);
	}
	else
	{
		if (listing->recursive_depth)
			ft_lstadd_back(directories, \
					ft_lstnew(NULL, sizeof(NULL)));
		if (errno == ENOTDIR && is_a_valid_file(folder_name))
			ft_lstadd(file_list, ft_lstnew(folder_name, \
						ft_strlen(folder_name) + 1));
		else
			no_such_file_or_dir(folder_name, listing, directories);
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

void				start_listing(t_list **arggs, t_listing *listing)
{
	t_list			*dir_list;
	t_list			*file_list;
	t_list			*arg;
	char			*f_nam;

	setup(&dir_list, &file_list, arggs, &arg);
	while (arg)
	{
		f_nam = ft_strdup((char*)arg->content);
		if (listing->handle_singles \
				&& link_is_a_file(f_nam, arggs, arg, listing))
			ft_lstadd_back(&file_list, ft_lstnew(f_nam, ft_strlen(f_nam) + 1));
		else
			read_directory(f_nam, &dir_list, &file_list, listing);
		arg = arg->next;
		free(f_nam);
	}
	reverse_lists_if_needed(arggs, &file_list, &dir_list, listing);
	if (listing->d)
		print_file_list(*arggs, arggs, listing);
	print_files_and_directories(arggs, &file_list, listing);
	if (dir_list)
		do_directories(*arggs, dir_list, listing);
	clean_listing(dir_list, file_list);
}
