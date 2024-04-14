/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:23:19 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:23:22 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		un = -n;
	}
	else
		un = n;
	if (un > 9)
	{
		ft_putnbr_fd(un / 10, fd);
		ft_putchar_fd((un % 10) + 48, fd);
	}
	else
		ft_putchar_fd(un + 48, fd);
}
