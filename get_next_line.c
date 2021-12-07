/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:29:07 by cnysten           #+#    #+#             */
/*   Updated: 2021/12/07 20:20:28 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	line_len(const char *buf)
{
	size_t	i;

	if (!buf)
		return (0);
	i = 0;
	while ((buf)[i] != '\n')
		i++;
	return (i);
}

size_t	has_newline(const char *buf)
{
	size_t	i;

	i = 0;
	while ((buf)[i] != '\n')
		i++;
	return (i);
}

void	grow_buffer(void **buf, size_t len)
{
	void	*new;

	if (!buf || !*buf || len < 1)
		return ;
	new = malloc(len + BUFF_SIZE);
	if (!new)
		return ;
	ft_strncpy(new, *buf, len);
	free(*buf);
	*buf = new;
}

int	get_next_line(const int fd, char **line)
{
	static char	*fds[MAX_FD + 1];
	ssize_t		bytes_read;
	size_t		len;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (!fds[fd]) // Check if buffer is currently null
	{
		fds[fd] = (char *) malloc(BUFF_SIZE * sizeof (char));
		if (!fds[fd])
			return (-1); // Potential memory leak
		bytes_read = read(fd, fds[fd], BUFF_SIZE);
		if (bytes_read == 0) // EOF
			return (0);
		if (bytes_read < 0) // Error
			return (-1);
	}
	while (!ft_memchr(fds[fd], '\n', line_len(fds[fd]) + 1))
	{
		grow_buffer((void **) &fds[fd], BUFF_SIZE);
		bytes_read = read(fd, fds[fd], BUFF_SIZE);
		if (bytes_read == 0) // EOF
			return (0);
		if (bytes_read < 0) // Error
			return (-1);
	}
	len = line_len(fds[fd]);
	*line = ft_strnew(len + 1);
	if (!*line)
		return (-1);
	ft_memcpy((void *) *line, (const void *) fds[fd], len);
	ft_memmove((void *) fds[fd], (const void *)(fds[fd] + len + 1), BUFF_SIZE);
	return (1);
}
