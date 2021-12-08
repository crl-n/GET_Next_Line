/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:29:07 by cnysten           #+#    #+#             */
/*   Updated: 2021/12/08 21:37:29 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_to_line(char **line, char *fd, size_t len)
{
	char	*temp;

	if (!*line)
	{
		*line = ft_strnew(len);
		ft_strjoin(*line, ft_strsub(fd, 0, len));
	}
	else
	{
		temp = ft_strnew(ft_strlen(*line) + len);
		ft_strcpy(temp, *line);
		free(*line);
		*line = temp;
		ft_strjoin(*line, ft_strsub(fd, 0, len));
	}
}

int	get_next_line(const int fd, char **line)
{
	static char	*fds[MAX_FD + 1];
	ssize_t		bytes_read;

	if (fd < 0)
		return (-1);
	if (!fds[fd])
	{
		fds[fd] = (char *) malloc(BUFF_SIZE * sizeof (char));
		if (!fds[fd])
			return (-1);
		bytes_read = read(fd, fds[fd], BUFF_SIZE - 1);
	}
	while (!ft_strchr(fds[fd], '\n') && bytes_read == BUFF_SIZE - 1)
	{
		add_to_line(line, fds[fd], BUFF_SIZE);
		bytes_read = read(fd, fds[fd], BUFF_SIZE);
	}
	add_to_line(line, fds[fd], bytes_read);
	if (bytes_read > 0)
		return (1);
	if (bytes_read == 0)
		return (0);
	return (-1);
}
