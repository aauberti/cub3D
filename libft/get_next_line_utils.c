/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:41:01 by aauberti          #+#    #+#             */
/*   Updated: 2024/10/22 16:59:19 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_gnl(const char *s)
{
	char	*dst;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	while (i < len)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strchr_gnl(char *s, int c)
{
	while (*s && (char)c != *s)
		s++;
	if (*s || !(char)c)
		return (s);
	return (0);
}

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (dest);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*new_str;

	len_s1 = 0;
	len_s2 = 0;
	if (s1)
	{
		while (s1[len_s1])
			len_s1++;
	}
	if (s2)
	{
		while (s2[len_s2])
			len_s2++;
	}
	new_str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!new_str)
		return (NULL);
	ft_memcpy_gnl(new_str, s1, len_s1);
	ft_memcpy_gnl(&new_str[len_s1], s2, len_s2);
	new_str[len_s1 + len_s2] = '\0';
	return (new_str);
}
