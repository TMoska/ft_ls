/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 22:40:00 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/14 23:07:59 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

t_file	*setup_file(char *folder_name, char *directory, t_listing *listing)
{
	t_file		*file;

	file = malloc(sizeof(t_file));
	ft_bzero(file, sizeof(t_file));
	file->basename = directory;
	file->full_name = get_full_name(folder_name, file->basename);
	(void)listing;
	return (file);
}
