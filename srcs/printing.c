/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 20:16:22 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/19 05:28:32 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_folder(char *folder_name, t_listing *listing)
{
	if (listing->printed_something_already)
		ft_putstr("\n");
	else
		listing->printed_something_already = 1;
	ft_putstr(folder_name);
	ft_putstr(":\n");
}

t_bool		should_print_entry(t_file *file, t_listing *listing)
{
	return (*file->basename != '.' || listing->all || listing->handle_singles);
}

static void	print_total_block_size(t_list *dir_files)
{
	unsigned long long	total;
	char				*str;

	total = 0;
	while (dir_files)
	{
		total += lstat_or_stat((t_file*)dir_files->content)->st_blocks;
		dir_files = dir_files->next;
	}
	ft_putstr("total ");
	str = ft_itoa_ularge(total);
	ft_putstr(str);
	free(str);
	ft_putchar('\n');
}

static void	print_all(t_list *dir_files, t_strlens *strlens, t_listing *listing)
{
	t_file	*file;
	t_bool	first;

	first = 1;
	listing->printed_something_already = 1;
	while (dir_files)
	{
		file = (t_file*)dir_files->content;
		if (should_print_entry(file, listing))
		{
			if (first && listing->long_format && !listing->handle_singles)
				print_total_block_size(dir_files);
			print_single_file(file, listing, strlens);
			first = 0;
		}
		dir_files = dir_files->next;
	}
}

void		print_files(t_list *dir_files, t_listing *listing)
{
	t_strlens strlens;

	if (listing->long_format)
		formatting(&strlens, dir_files, listing);
	print_all(dir_files, &strlens, listing);
}
