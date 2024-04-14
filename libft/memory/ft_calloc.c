/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:10:57 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:11:00 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;

	if (!count || !size)
	{
		size = 1;
		count = 1;
	}
	dst = malloc(size * count);
	if (dst)
		ft_bzero(dst, size * count);
	return (dst);
}

void	ft_safe_free(void *mem)
{
	if (mem)
		free(mem);
}
