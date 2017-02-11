/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 19:46:22 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/11 19:50:54 by tmoska           ###   ########.fr       */
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
