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
	static char			buf[BUFF_SIZE];
	static unsigned int	start;
	static ssize_t		bytes_read;
	size_t				size;

	if (start == 0)
	{
		bytes_read = read(fd, &buf, BUFF_SIZE);
		printf("bread: %zd\n", bytes_read);
	}
	if (bytes_read == 0)
	{
		ft_putendl("EOF");
		return (0);
	}
	if (bytes_read < 0)
	{
		ft_putendl("ERROR");
		return (-1);
	}
	size = next_line_size(((const char *)buf + start)) + 1;
	*line = ft_strnew(size);
	if (!*line)
		return (-1);
	ft_strncpy(*line, ft_strsub((char const *) buf, start, size - 1), size - 1);
	start += size;
	if (start >= BUFF_SIZE)
		start = 0;
	return (1);
}
