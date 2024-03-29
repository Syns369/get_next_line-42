/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:44:12 by jdarcour          #+#    #+#             */
/*   Updated: 2022/12/02 15:23:37 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	j;
	size_t	len_dest;
	size_t	len_src;

	len_src = ft_strlen((char *)src);
	len_dest = ft_strlen(dst);
	index = len_dest;
	j = 0;
	if (size <= len_dest)
		return (len_src + size);
	while (src[j] && index + 1 < size)
		dst[index++] = src[j++];
	dst[index] = '\0';
	return (len_dest + len_src);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		return (ft_strlen((char *)src));
	}
	else
		return (ft_strlen((char *)src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		total_len;

	total_len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = malloc(sizeof(char) * (total_len));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen((char *)s1) + 1);
	ft_strlcat(str, s2, total_len);
	free((char *)s1);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen((char *)s))
		return (malloc(sizeof(char)));
	if (len > ft_strlen((char *)s + start))
		len = ft_strlen((char *)s + start);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (0);
	while (i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
