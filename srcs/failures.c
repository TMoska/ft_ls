/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 19:56:04 by tmoska            #+#    #+#             */
/*   Updated: 2017/02/06 03:36:46 by moska            ###   ########.fr       */
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
		ft_lstadd_back(directories, ft_lstnew(NULL, sizeof(NULL)));
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
	ft_putstr_fd("\nusage: ls [-ARadglort1] [file ...]\n", 2);
	exit(1);
}
