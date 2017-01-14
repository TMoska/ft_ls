/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 22:09:21 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/14 16:43:10 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static void		exit_if_arg_empty(char *arg)
{
	if (arg[0] == '\0')
	{
		ft_putendl_fd("ft_ls: fts_open: No such file or directory", 2);
		exit(1);
	}
}

static void		assign_option(char c, t_listing *listing)
{
	if (c == 'R')
		listing->recursive = 1;
	else if (c == 'a')
		listing->all = 1;
	else if (c == 'l')
		listing->long_format = 1;
	else if (c == 'r')
		listing->sort_reverse = 1;
	else if (c == 't')
		listing->sort_time_modified = 1;
	else
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
		ft_putstr_fd("usage: ls [-Ralrt] [file ...]\n", 2);
		exit(1);
	}
}

static void		handle_options(char *s, t_listing *listing)
{
	while (*s)
	{
		assign_option(*s, listing);
		s++;
	}
}

static void		prep_arguments(t_list **arguments)
{
	if (!(*arguments))
		ft_lst_push_front(arguments, ft_strdup("./"));
	ft_lstsort(arguments, &ft_strcmp);
}

int				main(int ac, char **av)
{
	int			i;
	t_list		*arguments;
	t_listing	listing;

	ft_bzero(&listing, sizeof(t_listing));
	arguments = NULL;
	i = 1;
	while (i < ac && av[i][0] != '\0' && av[i][0] == '-' && av[i][1] != '\0'
		&& !ft_strequ(av[i], "--"))
	{
		handle_options(av[i] + 1, &listing);
		i++;
	}
	if (i < ac && ft_strequ(av[i], "--"))
		i++;
	while (i < ac)
	{
		exit_if_arg_empty(av[i]);
		ft_lst_push_front(&arguments, av[i]);
		listing.arg_num++;
		i++;
	}
	prep_arguments(&arguments);
	handle_ls(&arguments, &listing);
	return (0);
}
