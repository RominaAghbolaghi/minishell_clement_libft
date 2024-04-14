/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:26:51 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:26:52 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;

	nlen = ft_strlen(needle);
	if (nlen == 0)
		return ((char *)haystack);
	while (*haystack && ft_strncmp(haystack, needle, nlen) != 0 && len > nlen)
	{
		haystack++;
		len--;
	}
	if (ft_strncmp(haystack, needle, nlen) == 0)
		return ((char *)haystack);
	return (NULL);
}
