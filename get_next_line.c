/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:29:07 by cnysten           #+#    #+#             */
/*   Updated: 2021/12/15 18:05:36 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static void	add_to_line(char **line, char **heap)
{
	char	*newline;
	size_t	len;

	newline = ft_strchr(*heap, '\n');
	if (!newline)
	{
		*line = ft_strdup(*heap);
		ft_strdel(heap);
	}
	else
	{
		*line = ft_strsub(*heap, 0, (newline - *heap));
		len = ft_strlen(newline + 1);
		ft_memcpy(*heap, newline + 1, len);
		(*heap)[len] = '\0';
		if ((*heap)[0] == '\0')
			ft_strdel(heap);
	}
}

static char	*buff_to_heap(char *buff, char *heap)
{
	char	*temp;

	if (!heap)
		heap = ft_strnew(0);
	temp = ft_strjoin(heap, buff);
	free(heap);
	return (temp);
}

int	get_next_line(const int fd, char **line)
{
	static char	*heap[MAX_FD + 1];
	char		buff[BUFF_SIZE + 1];
	ssize_t		bytes_read;

	if (fd < 0 || !line || fd > MAX_FD)
		return (-1);
	if (heap[fd])
	{
		add_to_line(line, &(heap[fd]));
		return (1);
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, &buff, BUFF_SIZE);
		if (bytes_read < 0)
			break ;
		buff[bytes_read] = '\0';
		heap[fd] = buff_to_heap(buff, heap[fd]);
		if (heap[fd][0] == '\0')
			ft_strdel(&(heap[fd]));
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0 && !heap[fd])
		return (0);
	add_to_line(line, &(heap[fd]));
	return (1);
}
