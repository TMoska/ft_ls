/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 16:59:22 by moska             #+#    #+#             */
/*   Updated: 2017/01/13 23:43:36 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static void     read_directory(char *folder_name, t_list **directories,
                t_list **failures)
{
  DIR *opened;
  t_list    *files;
  struct dirent *read;

  files = NULL;
  if ((opened = opendir(folder_name)))
  {
    while ((read = readdir(opened)))
      ft_lst_push_front(&files, ft_strdup(read->d_name));
    ft_lst_push_back(directories, files);
    closedir(opened);
  }
  else
  {
    ft_lst_push_back(directories, NULL);
    directory_open_failed(folder_name, failures);
  }
}

static t_bool   argument_is_invalid(char *name, t_list **arguments, t_list *arg,
                                  t_listing *listing)
{
  t_stat    stats;
  DIR       *opened;

  if (*(ft_strchr(name, '\0') - 1) == '/')
    return (0);
  if (lstat(name, &stats))
    ft_lst_removenode(arguments, arg);
  else if (S_ISLNK(stats.st_mode))
  {
    if((opened = opendir(name)))
    {
      closedir(opened);
      return (listing->long_format);
    }
    return (1);
  }
  return (0);
}

void            handle_ls(t_list **arguments, t_listing *listing)
{
  t_list    *directories;
  t_list    *failures;
  t_list    *arg;
  char      *folder_name;

  directories = NULL;
  failures = NULL;
  arg = *arguments;
  while (arg)
  {
    folder_name = arg->content;
    if (argument_is_invalid(folder_name, arguments, arg, listing))
      ft_lst_push_back(&failures, folder_name);
    else
      read_directory(folder_name, &directories, &failures);
    arg = arg->next;
  }
  // Todo:
  // Do failures
  handle_failures(arguments,  &directories, &failures, listing);
}
