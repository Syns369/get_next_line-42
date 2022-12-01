/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:49:27 by jdarcour          #+#    #+#             */
/*   Updated: 2022/12/01 20:37:43 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	i = 0;
	dest = s;
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
}

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_line_n_stash(char *str, char *stash, char	*line, char *buf)
{
	char	*tmp;

	tmp = ft_substr(str, 0, check_n(str) + 1);
	line = ft_strjoin(line, tmp);
	ft_strlcpy(stash, str + (check_n(str) + 1), ft_strlen(str) - check_n(str));
	free(tmp);
	free(buf);
	return (line);
}

char	*ft_read(char *line, char *stash, char *buf, int fd)
{
	int			ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == -1)
	{
		free(line);
		free(buf);
		return (NULL);
	}
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (check_n(buf) >= 0)
			return (get_line_n_stash(buf, stash, line, buf));
		line = ft_strjoin(line, buf);
		ret = read(fd, buf, BUFFER_SIZE);
	}
	if (ret == 0 && line[0] == '\0')
	{
		free(line);
		line = NULL;
	}
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[1024][BUFFER_SIZE + 1];
	char		*line;
	char		*buf;

	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	if (check_n(stash[fd]) >= 0)
		return (get_line_n_stash(stash[fd], stash[fd], line, buf));
	line = ft_strjoin(line, stash[fd]);
	ft_bzero(stash[fd], BUFFER_SIZE + 1);
	return (ft_read(line, stash[fd], buf, fd));
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line1;
// 	char	*line2;
// 	char	*line3;
// 	char	*line4;

// 	fd = open("test.txt", O_RDONLY);
// 	line1 = get_next_line(fd);
// 	printf("%s", line1);
// 	free(line1);
// 	line2 = get_next_line(fd);
// 	printf("%s", line2);
// 	free(line2);
// 	line3 = get_next_line(fd);
// 	printf("%s", line3);
// 	free(line3);
// 	line4 = get_next_line(fd);
// 	printf("%s", line4);
// 	free(line4);
// 	close(fd);
// 	return (0);
// }
