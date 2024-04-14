/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:33:17 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:33:19 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	free_until(char **table, int max)
{
	int		i;

	i = 0;
	while (i < max)
		ft_safe_free(table[i++]);
	free(table);
}

void	*return_and_free(char **envp, int i)
{
	free_until(envp, i);
	return (NULL);
}
