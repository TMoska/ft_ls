/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 17:00:08 by tmoska            #+#    #+#             */
/*   Updated: 2017/01/15 22:04:58 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_strdup(char *src)
{
	char	*str;

	if (!src)
		printf("smth's fucked up\n");
	if ((str = (char*)malloc(sizeof(*str) * (ft_strlen(src) + 1))))
		ft_strcpy(str, src);
	else
		return (0);
	return (str);
}
