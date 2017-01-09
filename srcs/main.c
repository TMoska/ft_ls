/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 22:09:21 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/09 20:32:45 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static void		print_options(t_options *options)
{
	printf("recursive: %d\n", options->recursive);
	printf("all: %d\n", options->all);
	printf("long_format: %d\n", options->long_format);
	printf("sort_reverse: %d\n", options->sort_reverse);
	printf("sort_time_modified: %d\n", options->sort_time_modified);
}

static void		assign_option(char c, t_options *options)
{
	if (c == 'R')
		options->recursive = 1;
	else if (c == 'a')
		options->all = 1;
	else if (c == 'l')
		options->long_format = 1;
	else if (c == 'r')
		options->sort_reverse = 1;
	else if (c == 't')
		options->sort_time_modified = 1;
	else
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
		ft_putstr_fd("usage: ls [-Ralrt] [file ...]\n", 2);
		exit(1);
	}
}

static void		handle_options(char *s, t_options *options)
{
	while (*s)
	{
		assign_option(*s, options);
		s++;
	}
	print_options(options);
}

int				main(int ac, char **av)
{
	int			i;
	t_options	options;

	ft_bzero(&options, sizeof(t_options));
	i = 1;
	while (i < ac && av[i][0] != '\0' && av[i][0] == '-' && av[i][1] != '\0'
		&& !ft_strequ(av[i], "--"))
	{
		handle_options(av[i] + 1, &options);
		i++;
	}
	return (1);
}
