/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 20:16:22 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/18 01:37:32 by moska            ###   ########.fr       */
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

void      print_single_file(t_file *file, t_listing *listing, t_strlens *strlens)
{
  if (listing->long_format)
  {
    (void)strlens;
    // print all the stats BS
  }
  else
    ft_putendl(file->basename);
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
      // if (first && listing->long_format && !listing->handling_screwups)
        // print it ALL;
      print_single_file(file, listing, strlens);
      first = 0;
    }
    dir_files = dir_files->next;
  }
}

void    print_files(t_list *dir_files, t_listing *listing)
{
  t_strlens strlens;

  // if (listing->long_format)
  //   prep files
  print_all(dir_files, &strlens, listing);
}