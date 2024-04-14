/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:32:05 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/10 14:53:53 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	varcmp(t_var *var, t_var *ref)
{
	return (ft_strcmp(var->key, ref->key));
}

static void	key_len2(char *str, int *error)
{
	int	i;

	i = 0;
	if (ft_isnum(str[i]))
	{
		*error = 1;
		return ;
	}
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	if (!i || str[i] != 0)
		*error = 1;
}

static int	unset_rules(char *str)
{
	int		error;

	error = 0;
	key_len2(str, &error);
	if (error)
	{
		ft_putstr_fd("Minishell: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("' not a valid indentifier\n", 2);
	}
	return (error);
}

int	ft_unset(int argc, char **argv, t_list **env_var)
{
	int		i;
	t_var	var;

	i = 1;
	while (i < argc)
	{
		var.key = argv[i++];
		if (!ft_strcmp(var.key, "PWD"))
			g_unset = 1;
		if (unset_rules(var.key))
			return (0);
		else
			ft_lstremove_one_if(env_var, &var, varcmp, free_var);
	}
	return (0);
}
