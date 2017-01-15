/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 19:05:45 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/15 23:31:10 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int			is_a_dot_file(char *folder_name)
{
	char			*folder;

	folder = ft_strchr(folder_name, '\0');
	while (folder + 1 > folder_name)
	{
		if (*folder == '.' && *(folder - 1) == '/')
			return (1);
		folder--;
	}
	return (0);
}

int			do_print_folder(char *folder_name, t_listing *listing)
{
	if (listing->recursing && !listing->all)
		return (!is_a_dot_file(folder_name));
	return (1);
}

void		do_directories(t_list *arg, t_list *directory, t_listing *listing)
{
	char			*folder_name;
	t_bool			should_print_folder;

	while (arg)
	{
		folder_name = (char *)arg->content;
		should_print_folder = do_print_folder(folder_name, listing);
		if (listing->should_print_dir_names && should_print_folder)
			print_folder(folder_name, listing);
		if (directory->content)
		{
			do_single_directory(folder_name, (t_list*)(directory->content), should_print_folder, listing);
			while (((t_list*)directory->content))
			{
				printf("%s\n", ((t_list*)directory->content)->content);
				directory->content = ((t_list*)directory->content)->next;
			}
		}
		arg = arg->next;
		directory = directory->next;
	}
}
