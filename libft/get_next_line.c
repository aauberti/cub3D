/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:39:25 by aauberti          #+#    #+#             */
/*   Updated: 2024/10/22 16:59:29 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_read_data(int fd, char **str)
{
	char	*buffer;
	char	*tmp;
	int		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
	{
		free(buffer);
		return (-1);
	}
	buffer[bytes] = '\0';
	if (*str == NULL)
		*str = ft_strdup_gnl("");
	tmp = ft_strjoin_gnl(*str, buffer);
	free(*str);
	free(buffer);
	if (!tmp)
		return (-1);
	*str = tmp;
	return (bytes);
}

char	*ft_read_line(int fd, char *str)
{
	int	bytes;

	if (!str)
		str = ft_strdup_gnl("");
	while (1)
	{
		bytes = ft_read_data(fd, &str);
		if (bytes < 0)
		{
			free(str);
			return (NULL);
		}
		if (bytes == 0 && !str[0])
		{
			free(str);
			str = NULL;
			return (str);
		}
		if (ft_strchr_gnl(str, '\n') || bytes == 0)
			break ;
	}
	return (str);
}

char	*ft_line(char *str)
{
	char	*new;
	int		i;

	if (!str || !*str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	new = malloc(sizeof(char) * (i + (str[i] == '\n') + 1));
	if (!new)
		return (NULL);
	ft_memcpy_gnl(new, str, i);
	if (str[i] == '\n')
	{
		new[i] = '\n';
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_rest(char *str)
{
	char	*index;
	char	*rest;

	index = ft_strchr_gnl(str, '\n');
	if (!index)
	{
		free(str);
		return (NULL);
	}
	rest = ft_strdup_gnl(index + 1);
	free(str);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	str = ft_read_line(fd, str);
	if (!str)
		return (NULL);
	line = ft_line(str);
	str = ft_rest(str);
	if (str && str[0] == '\0')
	{
		free(str);
		str = NULL;
	}
	return (line);
}
