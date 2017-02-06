/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 19:05:45 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/06 03:35:09 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	if (listing->recursing && !listing->all && !listing->A)
		return (!is_a_dot_file(folder_name));
	return (1);
}

static void	check_permissions(char *folder_name, t_list *directory, \
	t_listing *listing)
{
	DIR				*opened;

	if (!(opened = opendir(folder_name)))
	{
		if (!(errno == ENOENT || errno == ENOTDIR))
		{
			ft_putstr_fd("ls: ", 2);
			perror(ft_basename(folder_name));
		}
	}
	else
	{
		closedir(opened);
		if ((t_list*)(directory->content))
			do_single_directory(folder_name, (t_list*)(directory->content), \
				listing);
	}
}

void		do_directories(t_list *arggs, t_list *directory, t_listing *listing)
{
	char			*folder_name;
	t_bool			should_print_folder;

	while (arggs)
	{
		folder_name = (char *)arggs->content;
		should_print_folder = do_print_folder(folder_name, listing);
		if (listing->should_print_dir_names && should_print_folder)
			print_folder(folder_name, listing);
		check_permissions(folder_name, directory, listing);
		arggs = arggs->next;
		directory = directory->next;
	}
}
