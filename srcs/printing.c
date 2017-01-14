/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 20:16:22 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/14 23:08:18 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	print_folder(char *folder_name, t_listing *listing)
{
	if (listing->printed_folder_already)
		ft_putstr("\n");
	else
		listing->printed_folder_already = 1;
	ft_putstr(folder_name);
	ft_putstr(":\n");
}
