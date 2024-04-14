/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:23:05 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:23:07 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "../char/char.h"
#include <unistd.h>

void	ft_putchar_fd(int c, int fd)
{
	char	buff[4];
	int		len;

	len = ft_utf8_encode(c, buff);
	write(fd, buff, len);
}
