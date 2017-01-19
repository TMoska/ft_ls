/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 20:48:47 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/19 01:08:14 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_push_front(t_list **begin_list, void *data)
{
	t_list	*new_list;

	new_list = ft_lst_create_elem(data);
	new_list->next = *begin_list;
	*begin_list = new_list;
}
