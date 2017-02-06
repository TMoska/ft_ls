/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 12:52:24 by moska             #+#    #+#             */
/*   Updated: 2017/02/06 05:07:36 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    del_files_n_fullnames(void **list_content, size_t *content_size)
{
  t_file *file;

  (void)content_size;
  file = (t_file*)(*list_content);
  if (file->full_name)
    ft_memdel((void**)&(file->full_name));
  if (file->basename)
    ft_memdel((void**)&(file->basename));
  if (file->owner)
    ft_memdel((void**)&(file->owner));
  if (file->group)
    ft_memdel((void**)&(file->group));
  if (file->stat && file->stat == file->lstat)
    ft_memdel((void**)&(file->stat));
  else
  {
    if (file->stat)
      ft_memdel((void**)&(file->stat));
    if (file->lstat)
      ft_memdel((void**)&(file->lstat));
  }
  if (file->file_size_first)
    ft_memdel((void**)&(file->file_size_first));
  if (file->file_size_second)
    ft_memdel((void**)&(file->file_size_second));
  ft_memdel((void**)&file);
}

void  del_file(t_file *file)
{
  ft_memdel((void**)&file);
}

void  deep_del_files(t_list **lst)
{
  t_list *next;

  while (*lst)
  {
    next = (*lst)->next;
    ft_lstdel((t_list**)&(*lst)->content, &ft_lst_clear);
    (*lst)->content_size = 0;
    ft_memdel((void**)lst);
    *lst = next;
  } 
}

void  del_deep_char(char **arr)
{
  char *str;
  char **arr_tmp;

  arr_tmp = arr;
  while (*arr)
  {
    str = *arr;
    arr++;
    free(str);
  }
  free(arr_tmp);
}