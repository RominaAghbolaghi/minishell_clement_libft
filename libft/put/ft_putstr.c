/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:23:29 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:23:30 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include <unistd.h>

void	ft_putstr(char *str)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
}

void	ft_putprintable(char *str)
{
	while (*str)
	{
		if (*str >= 32 && *str <= 126)
			write(1, str, 1);
		else
			write(1, ".", 1);
		str++;
	}
}

void	ft_putnl(char *str)
{
	ft_putstr(str);
	ft_putstr("\n");
}
