/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 19:56:04 by moska             #+#    #+#             */
/*   Updated: 2017/01/13 23:40:09 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static int is_a_valid_file(char *folder_name)
{
  DIR   *dir;
  struct dirent *read;
  char *path;
  char *short_name;
  int ret;

  ret = 0;
  path = ft_get_path(folder_name);
  short_name = ft_basename(folder_name);
  dir = opendir(path);
  while ((read = readdir(dir)))
    if (ft_strequ(short_name, read->d_name))
      ret = 1;
  free(path);
  closedir(dir);
  return (ret);
}

void    directory_open_failed(char *folder_name, t_list **failures)
{
  if (errno == ENOTDIR && is_a_valid_file(folder_name))
    ft_lst_push_front(failures, folder_name);
  else
  {
    if (errno == ENOENT || errno == ENOTDIR)
    {
      ft_putstr_fd("ft_ls: ", 2);
      ft_putstr_fd(folder_name, 2);
      ft_putendl_fd(": No such file or directory", 2);
    }
    else
    {
      ft_putstr_fd("ft_ls: ", 2);
      perror(ft_basename(folder_name));
    }
  }
}