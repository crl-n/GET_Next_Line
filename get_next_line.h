/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnysten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:38:50 by cnysten           #+#    #+#             */
/*   Updated: 2021/12/06 14:47:53 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 32
# define MAX_FD 256
# include <unistd.h>
# include <stdlib.h>

int		get_next_line(const int fd, char **line);
void	ft_putendl(char const *s);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strnew(size_t size);

#endif
