/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 20:16:22 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/18 21:58:27 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	print_folder(char *folder_name, t_listing *listing)
{
	if (listing->printed_folder_already)
		ft_putstr("\n");
	else
		listing->printed_folder_already = 1;
	ft_putstr(folder_name);
	ft_putstr(":\n");
}

t_bool        should_print_entry(t_file *file, t_listing *listing)
{
  return (*file->basename != '.' || listing->all || listing->handling_screwups);
}

static void print_symlink_arrow_link(t_file *file)
{
  char buff[BUFF];

  if (file->is_symlink)
  {
    ft_putstr(" -> ");
    write(1, buff, readlink(file->full_name, buff, BUFF));
  }
}

static void   print_time(t_file *file)
{
  char  *str;
  time_t  stat_time;
  time_t  diff;

  stat_time = to_lstat_or_not_to_lstat(file)->st_mtimespec.tv_sec;
  str = ft_strdup(ctime(&stat_time));
  write(1, str + 4, 7);
  diff = file->time_generated - stat_time;
  if (diff > SIX_MONTHS_SECONDS || diff < -SIX_MONTHS_SECONDS)
    write(1, str + 19, 5);
  else
    write(1, str + 11, 5);
  free(str);
}

static void   print_size(t_file *file, t_strlens *strlens)
{
  if (file->file_size_first)
  {
    ft_put_justified_str(file->file_size_first, strlens->major + 3, ' ', 1);
    ft_putstr(", ");
    ft_put_justified_str(file->file_size_second, strlens->file_size - strlens->major - 1, ' ', 1);
  }
  else
    ft_put_justified_str(file->file_size_second, strlens->file_size + (strlens->major ? 4 : 2), ' ', 1);;
}

static void print_options(t_file *file, t_strlens *strlens)
{
  ft_putchar(file->file_type);
  print_file_permissions(file);
  ft_put_justified_nbr(to_lstat_or_not_to_lstat(file)->st_nlink, strlens->nlink + 1, ' ', 1);
  ft_putstr(" ");
  ft_put_justified_str(file->owner, strlens->owner + 2, ' ', 0);
  ft_put_justified_str(file->group, strlens->group, ' ', 0);
  print_size(file, strlens);
  ft_putstr(" ");
  print_time(file);
}

void      print_single_file(t_file *file, t_listing *listing, t_strlens *strlens)
{
  if (listing->long_format)
  {
    print_options(file, strlens);
    ft_putchar(' ');
    ft_putstr(file->basename);
    print_symlink_arrow_link(file);
    ft_putchar('\n');
  }
  else
    ft_putendl(file->basename);
}

static void  print_total_block_size(t_list *dir_files)
{
  unsigned long long total;
  char *str;

  total = 0;
  while (dir_files)
  {
    total += to_lstat_or_not_to_lstat((t_file*)dir_files->content)->st_blocks;
    dir_files = dir_files->next;
  }
  ft_putstr("total ");
  str = ft_itoa_ularge(total);
  ft_putstr(str);
  free(str);
  ft_putchar('\n');
}

static void print_all(t_list *dir_files, t_strlens *strlens, t_listing *listing)
{
  t_file  *file;
  t_bool  first;

  first = 1;
  while (dir_files)
  {
    file = (t_file*)dir_files->content;
    if (should_print_entry(file, listing))
    {
      if (first && listing->long_format && !listing->handling_screwups)
        print_total_block_size(dir_files);
      print_single_file(file, listing, strlens);
      first = 0;
    }
    dir_files = dir_files->next;
  }
}

void    print_files(t_list *dir_files, t_listing *listing)
{
  t_strlens strlens;

  if (listing->long_format)
    long_format_files(&strlens, dir_files, listing);
  print_all(dir_files, &strlens, listing);
}