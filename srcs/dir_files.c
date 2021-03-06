/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 22:40:00 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/30 17:36:57 by moska            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_bool	setup_stats(t_file *file)
{
	file->lstat = malloc(sizeof(t_stat));
	if (lstat(file->full_name, file->lstat))
	{
		perror(file->full_name);
		free(file->lstat);
		return (1);
	}
	file->stat = malloc(sizeof(t_stat));
	if (stat(file->full_name, file->stat))
		file->stat = file->lstat;
	file->is_symlink = S_ISLNK(file->lstat->st_mode);
	file->time_generated = time(NULL);
	return (0);
}

char	*get_full_name(char *folder_name, char *basename)
{
	char *ret;

	if (*basename == '/')
		return (ft_strdup(basename));
	if (folder_name[ft_strlen(folder_name) - 1] == '/')
		ret = ft_strjoin(folder_name, basename);
	else
	{
		folder_name = ft_strjoin(folder_name, "/");
		ret = ft_strjoin(folder_name, basename);
		free(folder_name);
	}
	return (ret);
}

t_file	*setup_file(char *folder_name, char *file_name, t_listing *listing)
{
	t_file		*file;

	file = malloc(sizeof(t_file));
	ft_bzero(file, sizeof(t_file));
	file->basename = ft_strdup(file_name);
	file->full_name = get_full_name(folder_name, file->basename);
	if ((listing->recursive || listing->long_format ||
		listing->sort_time_modified) && setup_stats(file))
	{
		del_file(file);
		return (NULL);
	}
	return (file);
}
