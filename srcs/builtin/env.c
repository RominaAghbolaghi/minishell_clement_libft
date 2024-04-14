/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:32:05 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/04 15:14:24 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// int	ft_env(t_list *env_var)
// {
// 	int		i;
// 	char	**envp;

// 	envp = build_env(env_var);
// 	if (!envp)
// 	{
// 		ft_putstr_fd("Minishell: env: ", 2);
// 		ft_putstr_fd(strerror(errno), 2);
// 		ft_putstr_fd("\n", 2);
// 		return (errno);
// 	}
// 	i = 0;
// 	while (envp[i])
// 	{
// 		ft_putstr_fd(envp[i], STDOUT_FILENO);
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 		i++;
// 	}
// 	free_table(&envp);
// 	return (0);
// }

int	ft_env(t_list *env_var)
{
	t_var	var;

	while (env_var)
	{
		var = *(t_var *)env_var->content;
		if (ft_strcmp(var.key, "?") && var.data)
		{
			ft_putstr_fd(var.key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(var.data, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		env_var = env_var->next;
	}
	return (0);
}
