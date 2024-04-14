/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:25:33 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:25:33 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "../char/char.h"

int	ft_str_is_lowercase(char *str)
{
	while (*str && ft_islower(*str))
		str++;
	return (!*str || ft_islower(*str));
}
