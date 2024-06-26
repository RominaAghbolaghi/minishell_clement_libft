/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:34:00 by cbiteau           #+#    #+#             */
/*   Updated: 2024/04/13 12:15:33 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_all_pipes(t_tube *tube_list, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(tube_list[i][0]);
		close(tube_list[i][1]);
		i++;
	}
}

void	close_finish_tube(t_tube *tube_list, int forks_running, int fork_n)
{
	if (forks_running < (fork_n - 1))
		close(tube_list[forks_running][1]);
	if (forks_running != 0)
		close(tube_list[forks_running - 1][0]);
	free(tube_list);
}

void	execution_error_write(char *cmd, char *error)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	execution_error_status(char *cmd, char *error,
			int status, t_list **env_vars)
{
	set_status_env(env_vars, status);
	execution_error_write(cmd, error);
}
