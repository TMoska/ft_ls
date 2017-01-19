/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files_and_directories.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 01:22:28 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/19 02:59:58 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_file_list(t_list *file_list, t_list **arguments,\
		t_listing *listing)
{
	t_list *files;

	files = NULL;
	while (file_list)
	{
		ft_lst_push_front(&files, setup_file("./", (char*)file_list->content,\
					listing));
		ft_lst_remove_if(arguments, file_list->content, &ft_ptrequ);
		file_list = file_list->next;
	}
	listing->handle_singles = 1;
	sort_files(&files, listing);
	print_files(files, listing);
	listing->handle_singles = 0;
}

void			print_files_and_directories(t_list **arguments,
		t_list **directories, t_list **file_list, t_listing *listing)
{
	if (*file_list && listing->should_handle_screwups)
	{
		print_file_list(*file_list, arguments, listing);
		ft_lstdel(file_list, NULL);
		listing->should_print_dir_names = 1;
	}
	listing->should_handle_screwups = 0;
	if (directories)
		do_directories(*arguments, *directories, listing);
}
