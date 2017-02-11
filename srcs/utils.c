/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 12:52:24 by moska             #+#    #+#             */
/*   Updated: 2017/02/11 19:53:24 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	if (file->stat && file->stat == file->lstat)
		ft_memdel((void**)&(file->stat));
	else if (file->stat)
		ft_memdel((void**)&(file->stat));
	else if (file->lstat)
		ft_memdel((void**)&(file->lstat));
	if (file->file_size_first)
		ft_memdel((void**)&(file->file_size_first));
	if (file->file_size_second)
		ft_memdel((void**)&(file->file_size_second));
	ft_memdel((void**)&file);
}

void	del_file(t_file *file)
{
	ft_memdel((void**)&file);
}

void	deep_del_files(t_list **lst)
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

void	del_deep_char(char **arr)
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
	if (arr_tmp)
		free(arr_tmp);
}

int		link_will_loop(char ***split_link, char ***split_path, \
		char link[BUFF], int i)
{
	if (ft_strequ((*split_path)[i - 1], **split_link) ||
			ft_strequ(link, "./") || ft_strequ(link, "."))
		return (1);
	return (0);
}
