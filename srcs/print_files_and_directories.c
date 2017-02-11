/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files_and_directories.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 01:22:28 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/11 19:42:07 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file_list(t_list *file_list, t_list **arguments, \
		t_listing *listing)
{
	t_list *files;
	t_file *file;

	files = NULL;
	while (file_list)
	{
		ft_lstadd(&files, ft_lstnew(file = setup_file("./", \
						(char*)file_list->content, listing), sizeof(t_file)));
		del_file(file);
		ft_lst_remove_if(arguments, file_list->content, &ft_strequ);
		file_list = file_list->next;
	}
	listing->handling_singles = 1;
	sort_files(&files, listing);
	print_files(files, listing);
	ft_lstdel(&files, &ft_lst_clear);
	listing->handling_singles = 0;
}

void	print_files_and_directories(t_list **arguments, \
	t_list **file_list, t_listing *listing)
{
	if (listing->d)
		return ;
	if (*file_list && listing->handle_singles)
	{
		print_file_list(*file_list, arguments, listing);
		listing->should_print_dir_names = 1;
	}
	listing->handle_singles = 0;
}
