/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:26:20 by hzakharc          #+#    #+#             */
/*   Updated: 2024/07/02 12:51:41 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*_read_data(int fd, char *s_buf)
{
	int		read_bytes;
	char	*buf;

	read_bytes = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	while (!ft_strchr(s_buf, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		s_buf = ft_strjoin(s_buf, buf);
	}
	free(buf);
	return (s_buf);
}

char		*get_next_line(int fd)
{
	static char *s_buf;
	char		*buf;

	if (fd <= 0 || buf == NULL || read(fd, 0, 0) < 0)
	{
		free(s_buf);
		return (NULL);
	}
	s_buf = _read_data(fd, s_buf);
	if (s_buf == NULL)
		return (NULL);
	buf = ft_substr(s_buf, 0, (s_buf - ft_strchr(s_buf, '\n')));
	if (buf == NULL)
		return (NULL);
	free(s_buf);
	return (buf);
}

#include <stdio.h>

int main(void)
{
	int fd;
	char *next_line;
	int count;

	fd = open("test.txt", O_RDONLY);
	count = 0;
	while (1)
	{
		next_line = get_next_line(fd);
		if (!next_line)
			break ;
		count++;
		printf("[%d]:%s\n", count, next_line);
		free(next_line);
	}
	
	close(fd);
	return (0);
}