/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <aauberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:28:16 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/11 14:17:03 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	int		len_total;
	int		i;
	int		j;
	char	*result;

	if (!s2)
		return (NULL);
	i = 0;
	len_total = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (len_total + 1));
	if (result == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}
