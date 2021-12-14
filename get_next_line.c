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
#include <stdio.h>

static int	has_newline(const char *buff, char **newline)
{
	if (buff)
		*newline = ft_strchr(buff, '\n');
	*newline = NULL;
	return (!(*newline == NULL));
}

static void	read_to_buff(const int fd, char *buff, ssize_t *bytes_read)
{
	if (buff)
		*bytes_read = read(fd, buff, BUFF_SIZE - 1);
}

static void	create_buff(char **buff, const int fd, ssize_t *bytes_read)
{
	*buff = ft_strnew(BUFF_SIZE);
	read_to_buff(fd, *buff, bytes_read);
}


static void	add_to_line(char **line, char *buff, char *newline)
{
	char	*temp;

	if (!*line && !newline)
		*line = ft_strdup(buff);
	else if (!*line && newline)
	{
		*line = ft_strsub(buff, 0, (newline - buff)); // What if len is 0?
		ft_strncpy(buff, (newline + 1), BUFF_SIZE);
	}
	else if (*line && !newline)
	{
		temp = ft_strjoin(*line, buff);
		free(*line);
		*line = temp;
	}
	else if (*line && newline)
	{
		temp = ft_strjoin(*line, ft_strsub(buff, 0, (newline - buff)));
		free(*line);
		*line = temp;
		ft_strncpy(buff, (newline + 1), BUFF_SIZE);
	}
}

int	get_next_line(const int fd, char **line)
{
	static char	*bufs[MAX_FD + 1];
	char		*newline;
	ssize_t		bytes_read;

	bytes_read = 0;
	if (!bufs[fd])
		create_buff(&bufs[fd], fd, &bytes_read);
	if (!bufs[fd])
		return (-1);
	while (!has_newline(bufs[fd], &newline))
	{
		add_to_line(line, bufs[fd], newline);
		read_to_buff(fd, bufs[fd], &bytes_read);
	}
	add_to_line(line, bufs[fd], newline);
	if (bytes_read == 0 && ft_strlen(bufs[fd]) == 0)
	{
		free(bufs[fd]);
		return (0);
	}
	return (1);
}
