/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_create_elem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 20:56:57 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/09 21:01:23 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lst_create_elem(void *data)
{
	t_list *new_list;

	new_list = malloc(sizeof(t_list));
	new_list->data = data;
	new_list->next = NULL;
	return (new_list);
}
