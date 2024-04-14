/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstr_strlen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:28:05 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:28:06 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wstring.h"
#include "../char/char.h"

int	ft_wstr_strlen(int *wstr)
{
	char	buff[4];
	int		strlen;

	strlen = 0;
	while (*wstr)
		strlen += ft_utf8_encode(*wstr++, buff);
	return (strlen);
}
