/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_single_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 22:30:46 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/21 05:58:30 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	recurse(t_list **arguments, t_listing *listing, t_bonus *bonus)
{
	int			recursive_loop;

	listing->should_print_dir_names = 1;
	recursive_loop = listing->recursing;
	listing->recursing = 1;
	listing->recursive_depth++;
	start_listing(arguments, listing, bonus);
	listing->recursing = recursive_loop;
}

static t_bool	link_to_self(t_file *file)
{
	char		link[BUFF];
	size_t		lu;

	if (file->is_symlink)
	{
		lu = readlink(file->full_name, link, BUFF);
		if (lu >= BUFF)
		{
			ft_putendl("Link filename too long");
			exit(1);
		}
		link[lu] = '\0';
		if (ft_strequ(link, "./") || ft_strequ(link, "."))
			return (1);
	}
	return (0);
}

static void		do_recursiveness(t_list *dir_files, t_listing *listing, \
	t_bonus *bonus)
{
	t_list		*folders;
	t_file		*file;

	folders = NULL;
	while (dir_files)
	{
		file = (t_file*)dir_files->content;
		if (file->stat->st_mode & S_IFDIR
				&& !ft_strequ(file->basename, ".")
				&& !ft_strequ(file->basename, "..")
				&& !link_to_self(file))
			ft_lst_push_front(&folders, file->full_name);
		dir_files = dir_files->next;
	}
	if (folders)
		recurse(&folders, listing, bonus);
}

void			do_single_directory(char *folder_name, t_list *directory\
	, t_listing *listing, t_bonus *bonus)
{
	t_list		*dir_files;
	t_file		*file;
	t_bool		should_print_folder;

	should_print_folder = do_print_folder(folder_name, listing);
	dir_files = NULL;
	while (directory && (file = setup_file(folder_name,\
					ft_strdup((char*)directory->content), listing)))
	{
		ft_lst_push_front(&dir_files, file);
		directory = directory->next;
	}
	if (dir_files)
	{
		sort_files(&dir_files, listing);
		if (should_print_folder)
			print_files(dir_files, listing, bonus);
		if (listing->recursive)
			do_recursiveness(dir_files, listing, bonus);
	}
}
