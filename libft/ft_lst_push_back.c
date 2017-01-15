/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 15:38:07 by moska             #+#    #+#             */
/*   Updated: 2017/01/15 23:09:17 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lst_push_back(t_list **begin_list, void *data)
{
	t_list	*new_list;
	t_list	*tmp;

	tmp = *begin_list;
	new_list = ft_lst_create_elem(data);
	if (*begin_list)
	{
		while ((*begin_list)->next)
			*begin_list = (*begin_list)->next;
		(*begin_list)->next = new_list;
		*begin_list = tmp;
	}
	else
		*begin_list = new_list;
}
