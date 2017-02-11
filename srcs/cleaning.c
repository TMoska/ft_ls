/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 19:46:22 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/11 21:01:57 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	clean_listing(t_list *dir_list, t_list *file_list)
{
	if (dir_list)
		deep_del_files(&dir_list);
	if (file_list)
		ft_lstdel(&file_list, &ft_lst_clear);
}

void	del_lstat_and_stat(t_file *file)
{
	if (file->stat && file->stat == file->lstat)
		ft_memdel((void**)&(file->stat));
	else
	{
		if (file->stat)
			ft_memdel((void**)&(file->stat));
		if (file->lstat)
			ft_memdel((void**)&(file->lstat));
	}
}

void	del_files_n_fullnames(void **list_content, size_t *content_size)
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
	del_lstat_and_stat(file);
	if (file->file_size_first)
		ft_memdel((void**)&(file->file_size_first));
	if (file->file_size_second)
		ft_memdel((void**)&(file->file_size_second));
	ft_memdel((void**)&file);
}
