/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:31:34 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/09 18:01:18 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft.h"
#include <stdlib.h> // exit

typedef char 		t_bool;

typedef struct 	s_options
{
	t_bool		recursive;
	t_bool 		all;
	t_bool		long_format;
	t_bool		sort_reverse;
	t_bool		sort_time_modified;
}				t_options;

#endif