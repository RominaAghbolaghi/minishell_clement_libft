/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:25:25 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:25:26 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"
#include "../char/char.h"

int	ft_str_is_alpha(char *str)
{
	while (*str && ft_isalpha(*str))
		str++;
	return (!*str || ft_isalpha(*str));
}
