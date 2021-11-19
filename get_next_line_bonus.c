/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeanuts <mpeanuts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 20:57:29 by mpeanuts          #+#    #+#             */
/*   Updated: 2021/11/19 20:57:30 by mpeanuts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	len_before_nl(char *buf)
{
	size_t	count;

	count = 0;
	while (*buf != '\n')
	{
		count++;
		buf++;
	}
	return (count);
}

char	*truncate_line(char **fd_buf)
{
	char	*line;
	char	*tmp;
	size_t	len;

	len = len_before_nl(*fd_buf);
	line = ft_substr(*fd_buf, 0, len + 1);
	tmp = ft_strdup(&(*fd_buf)[len + 1]);
	if (!tmp)
		return (NULL);
	free(*fd_buf);
	if (tmp[0] == '\0')
	{
		free(tmp);
		*fd_buf = NULL;
	}
	else
		*fd_buf = tmp;
	return (line);
}

char	*return_and_truncate(char **fd_buf)
{
	char	*line;

	if (ft_strchr(*fd_buf, '\n'))
		line = truncate_line(fd_buf);
	else
	{
		line = ft_strdup(*fd_buf);
		if (!line)
			return (NULL);
		free (*fd_buf);
		*fd_buf = NULL;
	}
	return (line);
}

char	*save(char *buf, char **fd_buf)
{
	char	*tmp;

	if (!*fd_buf)
		*fd_buf = ft_strdup(buf);
	else
	{
		tmp = ft_strjoin(*fd_buf, buf);
		free(*fd_buf);
		*fd_buf = tmp;
	}
	return (*fd_buf);
}

char	*get_next_line(int fd)
{
	static char	*fd_buf[MAX_FD];
	int			count_read;
	char		buf[BUFFER_SIZE + 1];

	count_read = 1;
	if (fd < 0 || fd > MAX_FD || read(fd, 0, 0) < 0)
		return (NULL);
	if (fd_buf[fd])
		if (ft_strchr(fd_buf[fd], '\n'))
			return (return_and_truncate(&fd_buf[fd]));
	while (count_read > 0)
	{
		count_read = read(fd, buf, BUFFER_SIZE);
		if (count_read < 1 && !fd_buf[fd])
			return (NULL);
		buf[count_read] = '\0';
		if (!save(buf, &fd_buf[fd]))
			return (NULL);
		if (ft_strchr(fd_buf[fd], '\n'))
			break ;
	}
	return (return_and_truncate(&fd_buf[fd]));
}
