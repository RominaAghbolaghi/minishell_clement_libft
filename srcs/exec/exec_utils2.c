/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:33:49 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:33:50 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	sig_handler(int signal_no)
{
	(void)signal_no;
}

int	handle_dup2_error(t_tube *tube_list)
{
	execution_error_write("dup2 fail", strerror(errno));
	free(tube_list);
	return (errno + 2);
}

void	add_ls_color(t_command *command)
{
	char	*arg_string;
	t_list	*new;

	arg_string = ft_strdup(LS_COLOR);
	if (!arg_string)
		return ;
	new = ft_lstnew(arg_string);
	if (!new)
	{
		free(arg_string);
		return ;
	}
	ft_lstadd_back(&command->args, new);
}
