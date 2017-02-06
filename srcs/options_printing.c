/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_printing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 01:50:30 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/06 06:33:04 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_symlink_arrow_link(t_file *file)
{
	char *buff;

	buff = ft_memalloc(BUFF);
	if (file->is_symlink)
	{
		ft_putstr(" -> ");
		write(1, buff, readlink(file->full_name, buff, BUFF));
	}
	free(buff);
}

static void	print_time(t_file *file)
{
	char	*str;
	time_t	stat_time;
	time_t	diff;
	char	**str_arr;

	stat_time = multios_time(lstat_or_stat(file));
	str = ctime(&stat_time);
	str_arr = ft_strsplit(str, ' ');
	str_arr[4][ft_strlen(str_arr[4]) - 1] = '\0';
	str_arr[3][5] = '\0';
	ft_put_justified_str(str_arr[1], 3, ' ', 0);
	ft_put_justified_str(str_arr[2], 3, ' ', 1);
	diff = time(NULL) - stat_time;
	if (ft_atoi(str_arr[4]) >= 10000)
		ft_put_justified_str(str_arr[4], 7, ' ', 1);
	else if (diff > SIX_MONTHS_SECONDS || diff < 0)
		ft_put_justified_str(str_arr[4], 6, ' ', 1);
	else
		ft_put_justified_str(str_arr[3], 6, ' ', 1);
	del_deep_char(str_arr);
}

static void	print_size(t_file *file, t_strlens *strlens)
{
	if (file->file_size_first)
	{
		ft_put_justified_str(file->file_size_first, strlens->major + 3, ' ', 1);
		ft_putstr(", ");
		ft_put_justified_str(file->file_size_second,\
				strlens->file_size - strlens->major - 1, ' ', 1);
	}
	else
		ft_put_justified_str(file->file_size_second, strlens->file_size +\
				(strlens->major ? 4 : 2), ' ', 1);
}

static void	print_options(t_file *file, t_strlens *strlens, t_listing *listing)
{
	ft_putchar(file->file_type);
	print_file_permissions(file);
	ft_put_justified_nbr(lstat_or_stat(file)->st_nlink,\
			strlens->nlink + 1, ' ', 1);
	ft_putstr(" ");
	if (!listing->g && !listing->o)
	{
		ft_put_justified_str(file->owner, strlens->owner + 2, ' ', 0);
		ft_put_justified_str(file->group, strlens->group, ' ', 0);
	}
	else if (!listing->g && listing->o)
		ft_put_justified_str(file->owner, strlens->owner, ' ', 0);
	else if (listing->g && !listing->o)
		ft_put_justified_str(file->group, strlens->group, ' ', 0);
	print_size(file, strlens);
	ft_putstr(" ");
	print_time(file);
}

void		print_single_file(t_file *file, t_listing *listing, \
	t_strlens *strlens)
{
	if (listing->long_format)
	{
		print_options(file, strlens, listing);
		ft_putchar(' ');
		ft_putstr(file->basename);
		print_symlink_arrow_link(file);
		ft_putchar('\n');
	}
	else
		ft_putendl(file->basename);
}
