/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:22:29 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:22:29 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"
#include <stdlib.h>

static int	ft_len(int n)
{
	int			i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void	ft_compute(unsigned int n, char *dest, int len)
{
	while (len >= 0)
	{
		dest[len--] = (n % 10) + 48;
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		len;

	len = ft_len(n);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	if (n < 0)
	{
		dest[0] = '-';
		ft_compute((unsigned int) -n, dest + 1, len - 2);
	}
	else
		ft_compute((unsigned int)n, dest, len - 1);
	return (dest);
}
