/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:32:05 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/04 15:14:03 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	key_len(char *str, int *error)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	if (!i || (str[i] != '='
			&& ft_memcmp(str + i, "+=", 2) && str[i] != 0))
	{
		*error = 1;
		return (-1);
	}
	return (i);
}

char	*catch_key(char **str, int *error, int *append)
{
	int		i;
	char	*dest;

	if (ft_isnum(**str))
	{
		*error = 1;
		return (NULL);
	}
	i = key_len(*str, error);
	if (i < 0)
		return (NULL);
	if (!ft_memcmp((*str) + i, "+=", 2))
		*append = true;
	else
		*append = false;
	dest = ft_substr(*str, 0, i);
	if (!dest)
		return (NULL);
	if ((*str)[i])
		(*str) += 1;
	(*str) += i + *append;
	return (dest);
}
