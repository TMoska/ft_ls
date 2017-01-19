/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 20:18:13 by moska             #+#    #+#             */
/*   Updated: 2017/01/19 03:00:02 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_stat		*lstat_or_stat(t_file *file)
{
	if (file->is_symlink)
		return (file->lstat);
	else
		return (file->stat);
}

static int	sort_by_basename(void *one, void *two)
{
	int		diff;
	char	*one_basename;
	char	*two_basename;

	one_basename = ((t_file*)one)->basename;
	two_basename = ((t_file*)two)->basename;
	diff = ft_strcmp(one_basename, two_basename);
	return (diff);
}

static int	sort_by_time(void *one, void *two)
{
	int		diff;
	t_stat	*one_stat;
	t_stat	*two_stat;

	one_stat = lstat_or_stat((t_file*)one);
	two_stat = lstat_or_stat((t_file*)two);
	diff = two_stat->st_mtimespec.tv_sec - one_stat->st_mtimespec.tv_sec;
	if (!diff)
		return (sort_by_basename(one, two));
	else
		return (diff);
}

void		sort_files(t_list **dir_files, t_listing *listing)
{
	if (listing->sort_time_modified)
		ft_lstsort(dir_files, &sort_by_time);
	else
		ft_lstsort(dir_files, &sort_by_basename);
	if (listing->sort_reverse)
		ft_lstrev(dir_files);
}
