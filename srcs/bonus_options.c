/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 05:27:05 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/25 20:39:14 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				handle_bonus(char c, t_listing *listing)
{
	if (c == 'd')
		listing->d = 1;
	else if (c == '1')
	{
		listing->one = 1;
		listing->long_format = 0;
	}
	else if (c == 'o')
	{
		listing->o = 1;
		listing->long_format = 1;
	}
	else if (c == 'g')
	{
		listing->g = 1;
		listing->long_format = 1;
	}
	if (c == 'd' || c == '1' || c == 'o' || c == 'g')
		return (1);
	return (0);
}
