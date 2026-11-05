/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 16:13:19 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/05 16:13:20 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t		len;
	size_t		i;
	char		*str;

	len = ft_strlen(s);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*sres;
	int		i;

	if (s1 == NULL)
		return (ft_strdup(s2));
	sres = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (sres == NULL)
	{
		free (s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		sres[i] = s1[i];
		i++;
	}
	while (*s2)
		sres[i++] = *s2++;
	sres[i] = '\0';
	free (s1);
	return (sres);
}
