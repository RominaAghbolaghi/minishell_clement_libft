/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:32:05 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/14 18:37:53 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	is_str_numeric(char *str)
{
	if (*str == '+' || *str == '-')
		if (!*++str)
			return (false);
	while (*str)
	{
		if (!ft_isnum(*str))
			return (false);
		str++;
	}
	return (true);
}

int	exit_not_numeric(char *argv_1, int offset)
{
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(argv_1, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (EXIT_ERROR + offset);
}

static int	exit_value(int argc, char **argv, t_list **env_var, int offset)
{
	int		ret;

	(void)offset;
	if (argc == 2)
		ret = ft_atoi_max(argv[1]);
	else
		ret = ft_atoi(search_var(*env_var, "?"));
	if (ret == -1 || ret == -2)
		ret += 256;
	return ((unsigned)(ret + offset));
}

int	ft_exit(int argc, char **argv, t_list **env_var, t_bool in_pipes)
{
	int		offset;

	if (in_pipes)
		offset = IN_PIPES;
	else
		offset = NOT_IN_PIPES;
	if (isatty(STDIN_FILENO))
		ft_putstr("exit\n");
	if (argc >= 2 && !is_str_numeric(argv[1]))
		return (exit_not_numeric(argv[1], offset));
	if (argc > 2)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		edit_var(env_var, "?", "1");
		return (1);
	}
	else
		return (exit_value(argc, argv, env_var, offset));
}
