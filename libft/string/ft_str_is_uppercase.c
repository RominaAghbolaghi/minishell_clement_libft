/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:25:40 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:25:42 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "../char/char.h"

int	ft_str_is_uppercase(char *str)
{
	while (*str && ft_isupper(*str))
		str++;
	return (!*str || ft_isupper(*str));
}
