/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:31:34 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/14 16:45:22 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
**	stdlib - exit
*/

# include "libft.h"
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>
# include <errno.h>

typedef char		t_bool;
typedef struct stat	t_stat;

typedef struct		s_listing
{
	t_bool			recursive;
	t_bool			all;
	t_bool			long_format;
	t_bool			sort_reverse;
	t_bool			sort_time_modified;
	int				arg_num;
}					t_listing;

void				handle_ls(t_list **arguments, t_listing *listing);
void				directory_open_failed(char *folder_name, t_list **failures);

#endif
