/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:27:13 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:27:16 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	cut;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	cut = ft_strlen(s1);
	while (cut && ft_strchr(set, s1[cut]))
		cut--;
	return (ft_substr(s1, 0, cut + 1));
}
