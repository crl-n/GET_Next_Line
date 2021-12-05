#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 32
# include <unistd.h>
# include <stdlib.h>

int		get_next_line(const int fd, char **line);
void	ft_putendl(char const *s);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strnew(size_t size);

#endif
