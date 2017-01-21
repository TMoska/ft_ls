/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:59:22 by moska             #+#    #+#             */
/*   Updated: 2017/01/21 16:23:55 by moska            ###   ########.fr       */
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
		return (0);
	while ((read = readdir(dir)))
		if (ft_strequ(short_name, read->d_name))
			ret = 1;
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
			ft_lstadd(&files, ft_lstnew(read->d_name, ft_strlen(read->d_name) + 1));
		ft_lst_push_back(directories, files);
		closedir(opened);
	}
	else
	{
		if (listing->recursive_depth)
			ft_lst_push_back(directories, NULL);
		if (errno == ENOTDIR && is_a_valid_file(folder_name))
			ft_lstadd(file_list, ft_lstnew(folder_name, ft_strlen(folder_name) + 1));
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

void				start_listing(t_list **arggs, t_listing *listing, \
	t_bonus *bonus)
{
	t_list			*dir_list;
	t_list			*file_list;
	t_list			*arg;
	char			*folder_name;

	setup(&dir_list, &file_list, arggs, &arg);
	while (arg)
	{
		folder_name = (char*)arg->content;
		if (listing->handle_singles \
				&& link_is_a_file(folder_name, arggs, arg, listing))
			ft_lst_push_back(&file_list, folder_name);
		else
			read_directory(folder_name, &dir_list, &file_list, listing);
		arg = arg->next;
	}
	reverse_lists_if_needed(arggs, &file_list, &dir_list, listing);
	if (bonus->d)
		print_file_list(*arggs, arggs, listing, bonus);
	print_files_and_directories(arggs, &file_list, listing, bonus);
	if (dir_list)
		do_directories(*arggs, dir_list, listing, bonus);
}
