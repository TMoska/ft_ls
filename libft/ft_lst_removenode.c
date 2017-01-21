/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_removenode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 18:11:17 by moska             #+#    #+#             */
/*   Updated: 2017/01/21 15:06:57 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lst_removenode(t_list **begin_list, t_list *removable)
{
	t_list	*old;

	if (begin_list && *begin_list && removable)
	{
		if (*begin_list == removable)
		{
			old = *begin_list;
			*begin_list = (*begin_list)->next;
			free(old->content);
			free(old);
		}
		else
			ft_lst_removenode(&((*begin_list)->next), removable);
	}
}
