/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 01:46:39 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/19 03:00:00 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		replace_if_greater(uintmax_t *old, uintmax_t new)
{
	if (new > *old)
		*old = new;
}

void		replace_if_greater_int(int *replace_if, int new_value)
{
	if (*replace_if < new_value)
		*replace_if = new_value;
}

void		replace_owner(t_strlens *strlens, t_file *file)
{
	struct passwd	*pass;

	pass = getpwuid(lstat_or_stat(file)->st_uid);
	if (pass)
		file->owner = ft_strdup(pass->pw_name);
	else
		file->owner = ft_itoa(lstat_or_stat(file)->st_uid);
	replace_if_greater(&strlens->owner, ft_strlen(file->owner));
}

void		replace_group(t_strlens *strlens, t_file *file)
{
	struct group	*group;

	group = getgrgid(lstat_or_stat(file)->st_gid);
	if (group)
		file->group = ft_strdup(group->gr_name);
	else
		file->group = ft_itoa(lstat_or_stat(file)->st_gid);
	replace_if_greater(&strlens->group, ft_strlen(file->group));
}
