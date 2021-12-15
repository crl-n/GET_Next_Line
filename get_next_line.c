/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:29:07 by cnysten           #+#    #+#             */
/*   Updated: 2021/12/15 17:09:13 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	has_newline(const char *buff, char **newline)
{
	if (buff && !*newline)
		*newline = ft_strchr(buff, '\n');
	return (!(*newline == NULL));
}

static int	read_to_buff(const int fd, char *buff, ssize_t *bytes_read)
{
	if (buff)
	{
		ft_strclr(buff);
		*bytes_read = read(fd, buff, BUFF_SIZE);
		if (*bytes_read < 0)
			return (-1);
	}
	return (0);
}

static int	create_buff(char **buff, const int fd, ssize_t *bytes_read)
{
	if (*buff)
		return (0);
	*buff = ft_strnew(BUFF_SIZE);
	if (!*buff)
		return (-1);
	if (read_to_buff(fd, *buff, bytes_read) == -1)
		return  (-1);
	return (1);
}

static void	add_to_line(char **line, char *buff, char *newline)
{
	char	*temp;

	if (!*line && !newline)
	{
		*line = ft_strnew(BUFF_SIZE + 1);
		ft_strncpy(*line, buff, BUFF_SIZE + 1);
	}
	else if (!*line && newline)
	{
		*line = ft_strsub(buff, 0, (newline - buff));
		ft_strncpy(buff, (newline + 1), BUFF_SIZE); // newline is not  necessarily null terminated
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

	if (fd < 0)
		return (-1);
	bytes_read = 0;
	newline = NULL;
	if (create_buff(&bufs[fd], fd, &bytes_read) == -1)
		return (-1);
	while (!has_newline(bufs[fd], &newline))
	{
		add_to_line(line, bufs[fd], newline);
		if (read_to_buff(fd, bufs[fd], &bytes_read) == -1)
			return (-1);
		if (bytes_read == 0)
			break ;
	}
	add_to_line(line, bufs[fd], newline);
	if (bytes_read == 0 && ft_strlen(bufs[fd]) == 0)
	{
		ft_strdel(&bufs[fd]);
		return (0);
	}
	return (1);
}
