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

static void	add_to_line(char **line, char **cache)
{
	char	*newline;
	char	*temp;

	newline = ft_strchr(*cache, '\n');
	if (!newline)
	{
		*line = ft_strdup(*cache);
		ft_strdel(cache);
	}
	else
	{
		*line = ft_strsub(*cache, 0, (newline - *cache));
		temp = ft_strdup(newline + 1);
		free(*cache);
		*cache = temp;
		if ((*cache)[0] == '\0')
			ft_strdel(cache);
	}
}

static char	*buff_to_cache(char *buff, char *cache)
{
	char	*temp;

	if (!cache)
		cache = ft_strnew(1);
	temp = ft_strjoin(cache, buff);
	free(cache);
	return (temp);
}

int	get_next_line(const int fd, char **line)
{
	static char	*caches[MAX_FD + 1];
	char		buff[BUFF_SIZE + 1];
	ssize_t		bytes_read;

	if (fd < 0 || !line || fd > MAX_FD)
		return (-1);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, &buff, BUFF_SIZE);
		if (bytes_read < 0)
			break ;
		buff[bytes_read] = '\0';
		caches[fd] = buff_to_cache(buff, caches[fd]);
		if (caches[fd][0] == '\0')
			ft_strdel(&(caches[fd]));
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0 && !caches[fd])
		return (0);
	add_to_line(line, &(caches[fd]));
	return (1);
}
