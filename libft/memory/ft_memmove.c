/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:11:38 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:11:39 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cdst;
	char	*csrc;

	cdst = (char *)dst;
	csrc = (char *)src;
	if (csrc < cdst)
	{
		csrc += len;
		cdst += len;
		while (len--)
			*--cdst = *--csrc;
	}
	else if (csrc != cdst)
		ft_memcpy(cdst, csrc, len);
	return (dst);
}
