/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file_permissions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 21:31:46 by moska             #+#    #+#             */
/*   Updated: 2017/01/18 22:04:26 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char        first_executable_permissions(mode_t mode)
{
  if (mode & S_ISUID)
    return ((mode & S_IXUSR) ? 's' : 'S');
  return ((mode & S_IXUSR) ? 'x' : '-');
}

char        second_executable_permissions(mode_t mode)
{
  if (mode & S_ISGID)
    return ((mode & S_IXGRP) ? 's' : 'S');
  return ((mode & S_IXGRP) ? 'x' : '-');
}

char        third_executable_permissions(mode_t mode)
{
  if (mode & S_ISVTX)
    return ((mode & S_IXOTH) ? 't' : 'T');
  return ((mode & S_IXOTH) ? 'x' : '-');
}

char        list_attributes(t_file *file)
{
  if ((!file->is_symlink && listxattr(file->full_name, NULL, 0, 0) > 0)
    || (file->is_symlink 
    && listxattr(file->full_name, NULL, 0, XATTR_NOFOLLOW) > 0))
    return ('@');
  return (' ');
}

void print_file_permissions(t_file *file)
{
  mode_t mode;

  mode = to_lstat_or_not_to_lstat(file)->st_mode;
  ft_putchar_if((mode & S_IRUSR), 'r', '-');
  ft_putchar_if(mode & S_IWUSR, 'w', '-');
  ft_putchar(first_executable_permissions(mode));
  ft_putchar_if(mode & S_IRGRP, 'r', '-');
  ft_putchar_if(mode & S_IWGRP, 'w', '-');
  ft_putchar(second_executable_permissions(mode));
  ft_putchar_if(mode & S_IROTH, 'r', '-');
  ft_putchar_if(mode & S_IWOTH, 'w', '-');
  ft_putchar(third_executable_permissions(mode));
  ft_putchar(list_attributes(file));  
}