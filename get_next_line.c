/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:49:27 by jdarcour          #+#    #+#             */
/*   Updated: 2022/11/26 14:15:35 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*get_line_n_stash(char *str, char *stash, char	*line)
{
	char	*tmp;

	tmp = ft_substr(str, 0, check_n(str) + 1);
	line = ft_strjoin(line, tmp);
	// ft_bzero(stash, BUFFER_SIZE + 1);
	ft_strlcpy(stash, str + check_n(str) + 1, BUFFER_SIZE + 1);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1] = {0};
	char		*line;
	char		*buf;

	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (!buf)
		return (NULL);
	if (stash[0] != '\0' && check_n(stash) == -1)
		line = ft_strjoin(line, stash);
	if (check_n(stash) >= 0)
	{
		line = get_line_n_stash(stash, stash, line);
		free(buf);
		return (line);
	}
	while (read(fd, buf, BUFFER_SIZE) > 0)
	{
		buf[BUFFER_SIZE] = '\0';
		if (check_n(buf) != -1)
		{
			line = get_line_n_stash(buf, stash, line);
			free(buf);
			return (line);
		}
		line = ft_strjoin(line, buf);
	}
	if (read(fd, buf, BUFFER_SIZE) == 0)
		return (NULL);
	free(buf);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line1;
	char	*line2;
	char	*line3;

	fd = open("test.txt", O_RDONLY);
	line1 = get_next_line(fd);
	printf("%s", line1);
	free(line1);
	line2 = get_next_line(fd);
	printf("%s", line2);
	free(line2);
	line3 = get_next_line(fd);
	printf("%s", line3);
	free(line3);
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}
