/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_single_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 22:30:46 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/06 05:20:33 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	recurse(t_list **arguments, t_listing *listing)
{
	int			recursive_loop;

	listing->should_print_dir_names = 1;
	recursive_loop = listing->recursing;
	listing->recursing = 1;
	listing->recursive_depth++;
	start_listing(arguments, listing);
	listing->recursing = recursive_loop;
}

static void		traceback_link_path(char ***split_link, char ***split_path,
	int *i, t_file *file)
{
	*split_path = ft_strsplit(file->full_name, '/');
	*i = ft_char_arr_len(*split_path);
	while (**split_link && ft_strequ(**split_link, ".."))
	{
		(*i)--;
		(*split_link)++;
	}
}

int	link_will_loop(char **split_link, char **split_path, char link[BUFF], int i)
{
	if (ft_strequ(split_path[i - 1], *split_link) ||
		ft_strequ(link, "./") || ft_strequ(link, "."))
	{

		del_deep_char(split_path);
		del_deep_char(split_link);
		return (1);
	}
	del_deep_char(split_path);
	del_deep_char(split_link);
	return (0);
}

static t_bool	link_to_self(t_file *file)
{
	char		link[BUFF];
	size_t		lu;
	char 		**split_link;
	char 		**split_path;
	int			i;

	split_link = NULL;
	split_path = NULL;
	if (file->is_symlink)
	{
		lu = readlink(file->full_name, link, BUFF);
		if (lu >= BUFF)
		{
			ft_putendl("Link filename too long");
			exit(1);
		}
		link[lu] = '\0';
		split_link = ft_strsplit(link, '/');
		traceback_link_path(&split_link, &split_path, &i, file);
		return (link_will_loop(split_path, split_link, link, i));
	}
	return (0);
}

static void		do_recursiveness(t_list *dir_files, t_listing *listing)
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
			ft_lstadd(&folders, ft_lstnew(file->full_name,
				ft_strlen(file->full_name) + 1));
		dir_files = dir_files->next;
	}
	if (folders)
	{
		recurse(&folders, listing);
		ft_lstdel(&folders, &ft_lst_clear);
	}
}

void			do_single_directory(char *folder_name, t_list *directory\
	, t_listing *listing)
{
	t_list		*dir_files;
	t_file		*file;
	t_bool		should_print_folder;

	should_print_folder = do_print_folder(folder_name, listing);
	dir_files = NULL;
	while (directory && (file = setup_file(folder_name, \
		(char*)directory->content, listing)))
	{
		ft_lstadd(&dir_files, ft_lstnew(file, sizeof(*file)));
		del_file(file);
		directory = directory->next;
	}
	if (dir_files)
	{
		sort_files(&dir_files, listing);
		if (should_print_folder)
			print_files(dir_files, listing);
		if (listing->recursive)
			do_recursiveness(dir_files, listing);
		ft_lstdel(&dir_files, &del_files_n_fullnames); // <<<<<<<<<<<
	}
}
