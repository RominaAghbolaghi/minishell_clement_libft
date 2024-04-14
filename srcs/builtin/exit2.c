/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:32:05 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/14 18:32:19 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_llong(unsigned long long res, int neg)
{
	if ((res > LLONG_MAX && neg > 0)
		|| ((((res > (LLONG_MAX)) && (res - 1) > (LLONG_MAX)) && neg < 0)))
		return (1);
	else
		return (0);
}

long long	ft_atoi_max(char *str)
{
	int					neg;
	int					i;
	unsigned long long	res;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		res = (res * 10) + (str[i++] - '0');
	if (ft_llong(res, neg))
		return (exit_not_numeric(str, 0));
	return ((long long)res * neg);
}
