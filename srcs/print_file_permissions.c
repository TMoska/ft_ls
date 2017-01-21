/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file_permissions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 21:31:46 by moska             #+#    #+#             */
/*   Updated: 2017/01/21 05:26:02 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	list_attributes(t_file *file)
{
	if ((!file->is_symlink && listxattr(file->full_name, NULL, 0, 0) > 0)
			|| (file->is_symlink
				&& listxattr(file->full_name, NULL, 0, XATTR_NOFOLLOW) > 0))
		return ('@');
	else if ((!file->is_symlink \
		&& acl_get_file(file->full_name, ACL_TYPE_EXTENDED)) ||
		(file->is_symlink && \
		acl_get_link_np(file->full_name, ACL_TYPE_EXTENDED)))
		return ('+');
	return (' ');
}

static void	user_permissions(mode_t mode)
{
	ft_putchar_if((mode & S_IRUSR), 'r', '-');
	ft_putchar_if(mode & S_IWUSR, 'w', '-');
	if (mode & S_ISUID)
		ft_putchar((mode & S_IXUSR) ? 's' : 'S');
	else
		ft_putchar((mode & S_IXUSR) ? 'x' : '-');
}

static void	group_permissions(mode_t mode)
{
	ft_putchar_if(mode & S_IRGRP, 'r', '-');
	ft_putchar_if(mode & S_IWGRP, 'w', '-');
	if (mode & S_ISGID)
		ft_putchar((mode & S_IXGRP) ? 's' : 'S');
	else
		ft_putchar((mode & S_IXGRP) ? 'x' : '-');
}

static void	other_permissions(mode_t mode)
{
	ft_putchar_if(mode & S_IROTH, 'r', '-');
	ft_putchar_if(mode & S_IWOTH, 'w', '-');
	if (mode & S_ISVTX)
		ft_putchar((mode & S_IXOTH) ? 't' : 'T');
	else
		ft_putchar((mode & S_IXOTH) ? 'x' : '-');
}

void		print_file_permissions(t_file *file)
{
	mode_t mode;

	mode = lstat_or_stat(file)->st_mode;
	user_permissions(mode);
	group_permissions(mode);
	other_permissions(mode);
	ft_putchar(list_attributes(file));
}
