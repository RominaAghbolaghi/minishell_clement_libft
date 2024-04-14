/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:27:01 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:27:04 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	char	*save;

	save = NULL;
	cc = (char)c;
	while (1)
	{
		if (*s == cc)
			save = (char *)s;
		if (!*s)
			return (save);
		s++;
	}
}
