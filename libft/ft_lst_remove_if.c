/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 00:38:15 by moska             #+#    #+#             */
/*   Updated: 2017/01/22 09:16:35 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lst_remove_if(t_list **begin_list, void *content, int (*cmp)())
{
	t_list	*match;

	if (*begin_list)
	{
		if (cmp((*begin_list)->content, content))
		{
			match = *begin_list;
			*begin_list = (*begin_list)->next;
			// if (match->content)
				// free(match->content);
			free(match);
			ft_lst_remove_if(begin_list, content, cmp);
		}
		else
			ft_lst_remove_if(&(*begin_list)->next, content, cmp);
	}
}
