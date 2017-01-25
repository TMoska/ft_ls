/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_printing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 01:50:30 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/25 20:36:40 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_symlink_arrow_link(t_file *file)
{
	char buff[BUFF];

	if (file->is_symlink)
	{
		ft_putstr(" -> ");
		write(1, buff, readlink(file->full_name, buff, BUFF));
	}
}

static void	print_time(t_file *file)
{
	char	*str;
	time_t	stat_time;
	time_t	diff;

	stat_time = lstat_or_stat(file)->st_mtimespec.tv_sec;
	str = ft_strdup(ctime(&stat_time));
	write(1, str + 4, 7);
	diff = time(NULL) - stat_time;
	if (stat_time >= 253402297140)
		write(1, str + 23, 6);
	else if (diff > SIX_MONTHS_SECONDS || diff < 0)
		write(1, str + 19, 5);
	else
		write(1, str + 11, 5);
	free(str);
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

static void	print_options(t_file *file, t_strlens *strlens, t_bonus *bonus)
{
	ft_putchar(file->file_type);
	print_file_permissions(file);
	ft_put_justified_nbr(lstat_or_stat(file)->st_nlink,\
			strlens->nlink + 1, ' ', 1);
	ft_putstr(" ");
	if (!bonus->g && !bonus->o)
	{
		ft_put_justified_str(file->owner, strlens->owner + 2, ' ', 0);
		ft_put_justified_str(file->group, strlens->group, ' ', 0);
	}
	else if (!bonus->g && bonus->o)
		ft_put_justified_str(file->owner, strlens->owner, ' ', 0);
	else if (bonus->g && !bonus->o)
		ft_put_justified_str(file->group, strlens->group, ' ', 0);
	print_size(file, strlens);
	ft_putstr(" ");
	print_time(file);
}

void		print_single_file(t_file *file, t_listing *listing, \
	t_strlens *strlens, t_bonus *bonus)
{
	if (listing->long_format)
	{
		print_options(file, strlens, bonus);
		ft_putchar(' ');
		ft_putstr(file->basename);
		print_symlink_arrow_link(file);
		ft_putchar('\n');
	}
	else
		ft_putendl(file->basename);
}
