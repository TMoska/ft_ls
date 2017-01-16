/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_single_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 22:30:46 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/17 00:30:04 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static	void	recurse(t_list **arguments, t_listing *listing)
{
	int		recursive_loop;

	listing->should_print_dir_names = 1;
	recursive_loop = listing->recursing;
	listing->recursing = 1;
	handle_ls(arguments, listing);
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
			exit (1);
		}
		link[lu] = '\0';
		if (ft_strequ(link, "./") || ft_strequ(link, ".")) // Todo: or ft_streq(*link, ".");
			return (1);
	}
	return (0);
}

static void		do_recursiveness(t_list *dir_files, t_listing *listing)
{
	t_list *folders;
	t_file *file;

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
		recurse(&folders, listing);
}

void	do_single_directory(char *folder_name, t_list *directory,
								t_bool should_print_folder, t_listing *listing)
{
	t_list			*dir_files;
	t_file			*file;
	char			*tmp;

	dir_files = NULL;
	while (directory)
	{
		tmp = ft_strdup((char*)directory->content);
		if ((file = setup_file(folder_name, tmp, listing)))
			ft_lst_push_front(&dir_files, file);
		directory = directory->next;
	}
	if (dir_files)
	{
		(void)should_print_folder;
		// sort
		// if (should_print_folder)
			// print files
		if (listing->recursive)
			do_recursiveness(dir_files, listing);
	}
}