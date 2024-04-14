/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:11:06 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:11:06 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*s1;
	char	*s2;

	s1 = (char *)dst;
	s2 = (char *)src;
	i = 0;
	while (i < n && s2[i] != (char)c)
	{
		s1[i] = s2[i];
		i++;
	}
	if (i == n)
		return (NULL);
	s1[i++] = (char)c;
	return (&s1[i]);
}
