/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 17:43:40 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/05 16:05:41 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char	*new_letf;
	size_t	len;
	size_t	i;

	i = 0;
	helper = ft_strchr(left, '\n');
	len = ft_strlen(helper);
	new_letf = NULL;
	if (len > 1)
		new_letf = malloc(len);
	if (new_letf)
	{
		while (i < len - 1)
		{
			new_letf[i] = helper[i + 1];
			i++;
		}
		new_letf[i] = '\0';
	}
	free (left);
	return (new_letf);
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
	static char	*left;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left = ft_read_to_left(left, fd);
	if (!left || left[0] == '\0')
	{
		free(left);
		left = NULL;
		return (NULL);
	}
	line = ft_line(left);
	if (line == NULL)
	{
		free (left);
		left = NULL;
		return (NULL);
	}
	left = ft_new_left(left);
	return (line);
}
