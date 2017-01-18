/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:07:06 by moska             #+#    #+#             */
/*   Updated: 2017/01/18 18:47:09 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static char   get_file_type(t_file *file)
{
  if (file->is_symlink)
    return ('l');
  if (S_ISBLK(file->stat->st_mode))
    return ('b');
  else if (file->stat->st_mode & S_IFCHR)
    return ('c');
  else if (S_ISSOCK(file->stat->st_mode))
    return ('s');
  else if (file->stat->st_mode & S_IFIFO)
    return ('p');
  else if (file->stat->st_mode & S_IFDIR)
    return ('d');
  return ('-');
}

static void   replace_if_greater(uintmax_t *old, uintmax_t new)
{
  if (new > *old)
    *old = new;
}

static void     replace_if_greater_int(int *replace_if
                      , int new_value)
{
  if (*replace_if < new_value)
    *replace_if = new_value;
}

static void replace_owner(t_strlens *strlens, t_file *file)
{
  struct passwd *pass;

  pass = getpwuid(to_lstat_or_not_to_lstat(file)->st_uid);
  if (pass)
    file->owner = ft_strdup(pass->pw_name);
  else
    file->owner = ft_itoa(to_lstat_or_not_to_lstat(file)->st_uid);
  replace_if_greater(&strlens->owner, ft_strlen(file->owner));
}

static void replace_group(t_strlens *strlens, t_file *file)
{
  struct group *group;

  group = getgrgid(to_lstat_or_not_to_lstat(file)->st_gid);
  if (group)
    file->group = ft_strdup(group->gr_name);
  else
    file->group = ft_itoa(to_lstat_or_not_to_lstat(file)->st_gid);
  replace_if_greater(&strlens->group, ft_strlen(file->group));
}

static int    get_size_string_length(t_file *file, uintmax_t *largest_major)
{
  uintmax_t minor;
  uintmax_t major;
  int       total;

  file->file_type = get_file_type(file);
  if (file->file_type == 'b' || file->file_type == 'c')
  {
    major = major(file->stat->st_rdev);
    minor = minor(file->stat->st_rdev);
    replace_if_greater(largest_major, major);
    file->file_size_first = ft_itoa_ularge(major);
    file->file_size_second = ft_itoa_ularge(minor);
    total = ft_strlen(file->file_size_first)
          + ft_strlen(file->file_size_second) + 2;
    return (total);
  }
  else
  {
    file->file_size_second = ft_itoa_ularge(to_lstat_or_not_to_lstat(file)->st_size);
    return(ft_strlen(file->file_size_second));
  }
}

void  long_format_files(t_strlens *strlens, t_list *dir_files, t_listing *listing)
{
  t_file *file;
  uintmax_t largest_nlink;
  uintmax_t largest_major;

  ft_bzero(strlens, sizeof(t_strlens));
  largest_nlink = 0;
  largest_major = 0;
  while (dir_files && (file = (t_file*)dir_files->content))
  {
    if (!should_print_entry(file, listing))
    {
      dir_files = dir_files->next;
      continue ;
    }
    replace_if_greater(&largest_nlink, to_lstat_or_not_to_lstat(file)->st_nlink);
    replace_if_greater_int(&strlens->file_size, get_size_string_length(file, &largest_major));
    replace_group(strlens, file);
    replace_owner(strlens, file);
    dir_files = dir_files->next;
  }
  strlens->nlink = ft_count_umax_digits(largest_nlink);

}