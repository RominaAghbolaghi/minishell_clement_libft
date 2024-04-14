/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:32:05 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/04 18:58:25 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_bool	is_valid_option(char *str)
{
	if (*str != '-')
		return (false);
	str++;
	while (*str == 'n')
		str++;
	if (*str == '\0')
		return (true);
	else
		return (false);
}

static int	number_of_options(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_option(argv[i]))
			return (i);
		i++;
	}
	return (i);
}

int	ft_echo(int argc, char **argv)
{
	int		i;
	t_bool	n_option;

	n_option = false;
	i = number_of_options(argc, argv);
	if (i > 1)
		n_option = true;
	while (i < argc)
	{
		ft_putstr(argv[i]);
		if ((i + 1) < argc)
			ft_putstr(" ");
		i++;
	}
	if (!n_option)
		ft_putstr("\n");
	return (0);
}
