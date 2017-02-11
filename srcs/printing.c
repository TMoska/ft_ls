/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 20:16:22 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/11 19:52:34 by tmoska           ###   ########.fr       */
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
	if (*file->basename != '.' || listing->all || listing->handling_singles)
		return (1);
	if (listing->cap_a)
	{
		if (ft_strequ(file->basename, ".") || ft_strequ(file->basename, ".."))
			return (0);
		else
			return (1);
	}
	return (0);
}

static void	print_total_block_size(t_list *dir_files, t_listing *listing)
{
	unsigned long long	total;
	char				*str;
	t_file				*file;

	total = 0;
	while (dir_files)
	{
		file = (t_file*)dir_files->content;
		if (!is_a_dot_file(file->full_name) || listing->all || listing->cap_a)
			total += lstat_or_stat(file)->st_blocks;
		dir_files = dir_files->next;
	}
	ft_putstr("total ");
	str = ft_itoa_ularge(total);
	ft_putstr(str);
	free(str);
	ft_putchar('\n');
}

static void	print_all(t_list *dir_files, t_strlens *strlens,\
	t_listing *listing)
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
			if (first && listing->long_format && !listing->handling_singles)
				print_total_block_size(dir_files, listing);
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
