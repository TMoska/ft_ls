/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 05:27:05 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/21 05:38:10 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				handle_bonus(char c, t_listing *listing, t_bonus *bonus)
{
	if (c == 'd')
		bonus->d = 1;
	else if (c == '1')
	{
		bonus->one = 1;
		listing->long_format = 0;
	}
	else if (c == 'o')
	{
		bonus->o = 1;
		listing->long_format = 1;
	}
	else if (c == 'g')
	{
		bonus->g = 1;
		listing->long_format = 1;
	}
	if (c == 'd' || c == '1' || c == 'o' || c == 'g')
		return (1);
	return (0);
}
