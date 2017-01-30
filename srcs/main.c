/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 22:09:21 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/30 17:35:59 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		handle_options(char c, t_listing *listing)
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
	else if (!handle_bonus(c, listing))
		illegal_option(c);
}

static	void	setup(t_list **arguments, t_listing *listing)
{
	ft_bzero(listing, sizeof(t_listing));
	*arguments = NULL;
}

static void		prep_arguments_and_listing(t_list **arguments,\
	t_listing *listing)
{
	if (!(*arguments))
		ft_lstadd(arguments, ft_lstnew(".", 2));
	listing->should_print_dir_names = ft_lstsize(*arguments) > 1;
	listing->handle_singles = 1;
}

static void		push_arguments(int i, int ac, char **av, t_list **arguments)
{
	while (i < ac)
	{
		exit_if_arg_empty(av[i]);
		ft_lstadd(arguments, ft_lstnew(av[i], ft_strlen(av[i]) + 1));
		i++;
	}
}

int				main(int ac, char **av)
{
	int			i;
	t_list		*arguments;
	t_listing	listing;
	char		*s;

	setup(&arguments, &listing);
	i = 1;
	while (i < ac && av[i][0] != '\0' && av[i][0] == '-' && av[i][1] != '\0'
		&& !ft_strequ(av[i], "--"))
	{
		s = av[i] + 1;
		while (*s)
		{
			handle_options(*s, &listing);
			s++;
		}
		i++;
	}
	if (i < ac && ft_strequ(av[i], "--"))
		i++;
	push_arguments(i, ac, av, &arguments);
	prep_arguments_and_listing(&arguments, &listing);
	start_listing(&arguments, &listing);
	if (arguments)
		ft_lstdel(&arguments, &ft_lst_clear);
	return (0);
}
