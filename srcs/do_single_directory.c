/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_single_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 22:30:46 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/14 23:13:37 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	do_single_directory(char *folder_name, t_list *directory,
								t_bool should_print_folder, t_listing *listing)
{
	t_list			*dir_files;
	t_file			*file;

	dir_files = NULL;
	while (directory && (file = setup_file(folder_name,
			ft_strdup((char*)directory->content), listing)))
	{
		ft_lst_push_front(&dir_files, file);
		directory = directory->next;
	}
	(void)should_print_folder;
	// if (dir_files)
	// {
	// }
}
