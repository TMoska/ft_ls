/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 20:18:13 by moska             #+#    #+#             */
/*   Updated: 2017/02/06 06:28:56 by moska            ###   ########.fr       */
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
	diff = multios_time(two_stat) - multios_time(one_stat);
	if (!diff)
		return (sort_by_basename(one, two));
	else
		return (diff);
}

void		reverse_lists_if_needed(t_list **arggs, t_list **file_list, \
	t_list **dir_list, t_listing *listing)
{
	if (listing->sort_reverse)
	{
		ft_lstrev(arggs);
		ft_lstrev(file_list);
		ft_lstrev(dir_list);
	}
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
