/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:32:05 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/04 15:15:24 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	sort_vars(t_var **var_table)
{
	int		i;
	int		j;
	t_var	*temp;

	i = 0;
	while (var_table[i])
	{
		j = i + 1;
		while (var_table[j])
		{
			if (ft_strcmp(var_table[i]->key, var_table[j]->key) > 0)
			{
				temp = var_table[i];
				var_table[i] = var_table[j];
				var_table[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_sorted(t_var	**var_table)
{
	while (*var_table)
	{
		ft_putstr("declare -x ");
		ft_putstr((*var_table)->key);
		if ((*var_table)->data)
		{
			ft_putstr("=\"");
			ft_putstr((*var_table)->data);
			ft_putstr("\"");
		}
		ft_putstr("\n");
		var_table++;
	}
}

/*
	if (!ft_strcmp(var->key, "?")) or
	if (!ft_strcmp(var->key, "?") || !ft_strcmp(var->key, "_"))
*/
static void	ctreat_vartable(t_list *env_var, t_var	**var_table)
{
	t_var	*var;
	int		i;

	i = 0;
	while (env_var)
	{
		var = (t_var *)env_var->content;
		env_var = env_var->next;
		if (!ft_strcmp(var->key, "?") || !ft_strcmp(var->key, "_"))
			continue ;
		var_table[i++] = var;
	}
}

static t_bool	find_oldpwd(t_list *env_var)
{
	t_var	*var;

	while (env_var)
	{
		var = (t_var *)env_var->content;
		if (!ft_strcmp(var->key, "OLDPWD"))
			return (true);
		env_var = env_var->next;
	}
	return (false);
}

int	print_export(t_list *env_var)
{
	t_var	**var_table;

	var_table = ft_calloc(ft_lstsize(env_var), sizeof(t_var *));
	if (!var_table)
	{
		ft_log_error(strerror(errno));
		return (127);
	}
	if (!find_oldpwd(env_var))
		edit_var(&env_var, "OLDPWD", NULL);
	ctreat_vartable(env_var, var_table);
	sort_vars(var_table);
	print_sorted(var_table);
	ft_safe_free(var_table);
	return (0);
}
