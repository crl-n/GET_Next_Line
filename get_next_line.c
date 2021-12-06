/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:29:07 by cnysten           #+#    #+#             */
/*   Updated: 2021/12/06 20:46:41 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	next_line_size(const char *buf)
{
	size_t	i;

	i = 0;
	while ((buf)[i] != '\n')
		i++;
	return (i);
}

int	get_next_line(const int fd, char **line)
{
	static char	*fds[MAX_FD + 1];
	ssize_t		bytes_read;
	size_t		size;

	if (fd < 0 || *line)
		return (-1);
	if (fds[fd])
	{

	}
	else
	{
		fds[fd] = (char *) malloc(BUFF_SIZE * sizeof (char)); // 
		bytes_read = read(fd, fds[fd], BUFF_SIZE);
		printf("bread: %zd\n", bytes_read);
		if (bytes_read == 0)
			return (0);
		if (bytes_read < 0)
			return (-1);
		if (!memchr((void *) fds[fd], '\n', bytes_read)
				ft_memrealloc();
		else
			*line = ft_strnew(bytes_read);
		if (!*line)
			return (-1);
		ft_strncpy(*line, start, size - 1), size - 1);
		start += size;
		if (start >= BUFF_SIZE)
			start = 0;
	}
	return (1);
}
