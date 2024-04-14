/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:32:05 by rmohamma          #+#    #+#             */
/*   Updated: 2024/03/08 14:32:07 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	add_var2(t_list **var_list, char *key, char *value)
{
	t_var	*var;
	t_list	*elem;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
	{
		load_var_error(ENV_VAR_ERROR, NULL, NULL);
		return (false);
	}
	var->key = ft_strdup(key);
	if (var->key && value)
		var->data = ft_strdup(value);
	if (!var->key || (value && !var->data))
	{
		load_var_error(ENV_VAR_ERROR, var, NULL);
		return (false);
	}
	elem = ft_lstnew(var);
	if (!elem)
	{
		load_var_error(ENV_VAR_ERROR, var, NULL);
		return (false);
	}
	ft_lstadd_back(var_list, elem);
	return (true);
}

/*
	Editing the variable is essential for Unix procedurial vision.
	We look through if the key of the current variable matches the specified key.
If there is a value specified, we free the data of the bvariable and replace it.
	We go through the the next element in the linked list.
	If the variable with the specified key does not exisr, add a new variable.
*/
static int	delete_value(t_list **var_list, char *key, char *value)
{
	t_var	*var;
	t_list	*current;

	current = *var_list;
	while (current)
	{
		var = (t_var *)current->content;
		if (!ft_strcmp(var->key, key))
		{
			ft_safe_free(var->data);
			var->data = NULL;
			if (value)
			{
				var->data = ft_strdup(value);
				if (!var->data)
				{
					load_var_error(ENV_VAR_ERROR, NULL, NULL);
					return (1);
				}
			}
			return (0);
		}
		current = current->next;
	}
	return (2);
}

t_bool	edit_var2(t_list **var_list, char *key, char *value)
{
	int	resualt;

	resualt = delete_value(var_list, key, value);
	if (resualt == 2)
	{
		if (ft_strcmp(key, "PWD"))
			return (add_var2(var_list, key, value));
	}
	else if (resualt == 1)
		return (false);
	return (true);
}
