/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <aauberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:27:31 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/09 10:27:32 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	if (c == '\0')
		return (((char *)str) + i);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return (&((char *)str)[i]);
		i--;
	}
	if (str[0] == (char)c)
		return ((char *)str);
	return (NULL);
}
