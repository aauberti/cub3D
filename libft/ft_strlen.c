/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <aauberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:27:52 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/11 13:35:55 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	const char	*temp;

	temp = s;
	if (!s)
		return (0);
	while (*temp)
		temp++;
	return (temp - s);
}
