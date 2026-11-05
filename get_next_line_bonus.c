/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:03:54 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/05 16:45:27 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_line(char *left)
{
	int		i;
	char	*line;

	i = 0;
	while (left[i] != '\n' && left[i] != '\0')
		i++;
	line = malloc (i + 2);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (left[i] != '\n' && left[i] != '\0')
	{
		line[i] = left[i];
		i++;
	}
	if (left[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_new_left(char *left)
{
	char	*helper;
	char	*new_left;
	size_t	len;
	size_t	i;

	i = 0;
	helper = ft_strchr(left, '\n');
	len = ft_strlen(helper);
	new_left = NULL;
	if (len > 1)
		new_left = malloc(len);
	if (new_left)
	{
		while (i < len - 1)
		{
			new_left[i] = helper[i + 1];
			i++;
		}
		new_left[i] = '\0';
	}
	free (left);
	return (new_left);
}

char	*ft_read_to_left(char *left, int fd)
{
	char	*buf;
	ssize_t	n;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (free(left), NULL);
	n = 1;
	while (!ft_strchr(left, '\n') && n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
		{
			free(left);
			free(buf);
			return (NULL);
		}
		buf[n] = '\0';
		left = ft_strjoin(left, buf);
		if (left == NULL)
			break ;
	}
	free (buf);
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*left[FD_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	left[fd] = ft_read_to_left(left[fd], fd);
	if (!left[fd] || left[fd][0] == '\0')
	{
		free(left[fd]);
		left[fd] = NULL;
		return (NULL);
	}
	line = ft_line(left[fd]);
	if (line == NULL)
	{
		free (left[fd]);
		left[fd] = NULL;
		return (NULL);
	}
	left[fd] = ft_new_left(left[fd]);
	return (line);
}
