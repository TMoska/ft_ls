/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files_and_directories.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 01:22:28 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/21 16:26:41 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file_list(t_list *file_list, t_list **arguments, \
		t_listing *listing, t_bonus *bonus)
{
	t_list *files;

	files = NULL;
	while (file_list)
	{
		ft_lstadd(&files, ft_lstnew(setup_file("./", (char*)file_list->content,\
					listing), sizeof(t_file)));
		ft_lst_remove_if(arguments, file_list->content, &ft_ptrequ);
		file_list = file_list->next;
	}
	listing->handling_singles = 1;
	sort_files(&files, listing);
	print_files(files, listing, bonus);
	listing->handling_singles = 0;
}

void	print_files_and_directories(t_list **arguments, \
	t_list **file_list, t_listing *listing, t_bonus *bonus)
{
	if (bonus->d)
		return ;
	if (*file_list && listing->handle_singles)
	{
		print_file_list(*file_list, arguments, listing, bonus);
		ft_lstdel(file_list, NULL);
		listing->should_print_dir_names = 1;
	}
	listing->handle_singles = 0;
}
