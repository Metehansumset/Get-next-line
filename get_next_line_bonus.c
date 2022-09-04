/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumset <42istanbul.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:56:08 by msumset           #+#    #+#             */
/*   Updated: 2022/09/04 12:56:09 by msumset          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_read_file(char	*main_str, int fd)
{
	ssize_t	r;
	char	*buff;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	r = 1;
	buff[0] = '\0';
	while (!ft_strchr(buff, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			free(buff);
			return (NULL);
		}
		if (r == 0)
			break ;
		buff[r] = '\0';
		main_str = ft_strjoin(main_str, buff);
	}
	free(buff);
	return (main_str);
}

char	*ft_get_line(char *main_str)
{
	size_t	len;
	char	*line;

	len = 0;
	while (main_str[len] && main_str[len] != '\n')
		len++;
	line = (char *)malloc((len + 2) * sizeof(char));
	if (!line)
		return (NULL);
	len = 0;
	while (main_str[len] && main_str[len] != '\n')
	{
		line[len] = main_str[len];
		len++;
	}
	if (main_str[len] == '\n')
	{
		line[len] = main_str[len];
		len++;
	}
	line[len] = '\0';
	return (line);
}

char	*ft_new_main(char *main_str)
{
	size_t	i;
	size_t	i2;
	char	*new_str;

	i = 0;
	while (main_str[i] && main_str[i] != '\n')
		i++;
	if (!main_str[i] || !main_str[i + 1])
	{
		free(main_str);
		return (NULL);
	}
	new_str = (char *)malloc((ft_strlen(main_str) - i) * sizeof(char));
	if (!new_str)
		return (NULL);
	i2 = 0;
	while (main_str[i + 1 + i2])
	{
		new_str[i2] = main_str[i + 1 + i2];
		i2++;
	}
	new_str[i2] = '\0';
	free(main_str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*main_str[1000];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	*(main_str + fd) = ft_read_file(*(main_str + fd), fd);
	if (!(*(main_str + fd)))
		return (NULL);
	line = ft_get_line(*(main_str + fd));
	if (!line[0])
	{
		free(line);
		return (NULL);
	}
	*(main_str + fd) = ft_new_main(*(main_str + fd));
	return (line);
}
