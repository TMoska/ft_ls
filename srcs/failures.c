/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 19:56:04 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/21 04:45:32 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	no_such_file_or_dir(char *folder_name, t_listing *listing, \
	t_list **directories)
{
	if (errno == ENOENT || errno == ENOTDIR)
	{
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(folder_name, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else if (!listing->recursive_depth)
		ft_lst_push_back(directories, NULL);
}

void	exit_if_arg_empty(char *arg)
{
	if (arg[0] == '\0')
	{
		ft_putendl_fd("ls: fts_open: No such file or directory", 2);
		exit(1);
	}
}

void	illegal_option(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ls [-Radglort1] [file ...]\n", 2);
	exit(1);
}
