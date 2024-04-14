/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:11:52 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:11:53 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include <stdlib.h>

void	*ft_realloc(void *src, size_t size, size_t addbyte)
{
	char	*csrc;
	char	*cdest;

	csrc = (char *)src;
	cdest = (char *)malloc((size + addbyte) * sizeof(char));
	ft_memcpy(cdest, csrc, size);
	free(src);
	return ((void *)cdest);
}
