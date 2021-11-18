#include "get_next_line.h"
// #define BUFFER_SIZE 1

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

static char	*get_return_value(char **buf)
{
	char	*line;
	char	*tmp;
	size_t	len;

	if (ft_strchr(*buf, '\n'))
	{
		len = len_before_nl(*buf);
		line = ft_substr(*buf, 0, len + 1);
		if (!line)
			return (NULL);
		tmp = ft_strdup(&(*buf)[len + 1]);
		if (!tmp)
			return (NULL);
		free(*buf);
		if (tmp[0] == '\0')
		{
			free(tmp);
			*buf = NULL;
		}
		else
			*buf = tmp;
	}
	else
	{
		line = ft_strdup(*buf);
		if (!line)
			return (NULL);
		free (*buf);
		*buf = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];
	static char		*fd_buf[256];
	int				count_read;
	char			*tmp;

	if (fd < 0 || fd > 256 || read(fd, 0, 0) < 0)
		return (NULL);
	count_read = read(fd, buf, BUFFER_SIZE);
	buf[count_read] = '\0';
	if (count_read < 1 && !fd_buf[fd])
		return (NULL);
	while (count_read > 0)
	{
		if (!fd_buf[fd])
		{
			fd_buf[fd] = ft_strdup(buf);
			if (!fd_buf[fd])
				return (NULL);
		}
		else
		{
			tmp = ft_strjoin(fd_buf[fd], buf);
			free (fd_buf[fd]);
			if (!tmp)
				return (NULL);
			fd_buf[fd] = tmp;
		}
		if (ft_strchr(fd_buf[fd], '\n'))
			break ;
		count_read = read(fd, buf, BUFFER_SIZE);
		buf[count_read] = '\0';
	}
	return (get_return_value(&fd_buf[fd]));
}
