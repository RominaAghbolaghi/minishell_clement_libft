/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:30:36 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:30:39 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse key=value
*/

t_var	*create_var(char *str)
{
	int		i;
	t_var	*var;

	errno = 0;
	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (load_var_error(ENV_VAR_ERROR, NULL, NULL));
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var->key = ft_substr(str, 0, i);
	if (!var->key)
		return (load_var_error(ENV_VAR_ERROR, var, NULL));
	if (str[i])
		str += i + 1;
	else
		str += i;
	var->data = ft_strdup(str);
	if (!var->data)
		return (load_var_error(ENV_VAR_ERROR, var, NULL));
	return (var);
}

void	free_var(void *mem)
{
	t_var	*var;

	var = (t_var *)mem;
	ft_safe_free(var->key);
	ft_safe_free(var->data);
	ft_safe_free(var);
}

/*
	targets a value of key.
*/

char	*search_var(t_list *var_list, char *key)
{
	t_var	*var;

	while (var_list)
	{
		var = (t_var *)var_list->content;
		if (!ft_strcmp(var->key, key))
			return (var->data);
		var_list = var_list->next;
	}
	return (NULL);
}

/*
	Adding a var or edit an existing one
*/

static t_bool	add_var(t_list **var_list, char *key, char *value)
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
	We look through if the key of the current variable matches the specified
	key.
	If there is a value specified, we free the data of the bvariable and r
	eplace it.
	We go through the the next element in the linked list.
	If the variable with the specified key does not exisr, add a new variable.
*/

t_bool	edit_var(t_list **var_list, char *key, char *value)
{
	t_var	*var;
	t_list	*current;

	current = *var_list;
	while (current)
	{
		var = (t_var *)current->content;
		if (!ft_strcmp(var->key, key))
		{
			if (value)
			{
				ft_safe_free(var->data);
				var->data = ft_strdup(value);
				if (!var->data)
				{
					load_var_error(ENV_VAR_ERROR, NULL, NULL);
					return (false);
				}
			}
			return (true);
		}
		current = current->next;
	}
	return (add_var(var_list, key, value));
}
