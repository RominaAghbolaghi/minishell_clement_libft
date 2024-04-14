/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:27 by cbiteau           #+#    #+#             */
/*   Updated: 2024/04/09 14:22:16 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
	Retrieving the value of the a variabe identified by the provided key.
		From the environment variables stored in a linked list.
	If the var is found, it returns the duplicate of the found variable.
	Else it returns an empty string.
*/

char	*get_var(char *key, t_list *env_var)
{
	char	*search;

	search = search_var(env_var, key);
	if (search)
		return (ft_strdup(search));
	return (ft_strdup(""));
}

/*
	If current is "?" we set the length of key to 1 and pass it.
	We return a string containing a "?" only.
	Else, we init the length to 0.
	While char is either numerical or '_' we increment the length of key.
	Key takes the extract from original string.
	We move the pointer past the extracted key and return the extracted key.
*/

char	*get_key(char **str, int *i)
{
	char	*key;

	if (**str == '?')
	{
		*i = 1;
		(*str) += *i;
		return (ft_strdup("?"));
	}
	*i = 0;
	while ((*str)[*i] && ((*str)[*i] == '_' || ft_isalnum((*str)[*i])))
		(*i)++;
	key = ft_substr(*str, 0, *i);
	(*str) += *i;
	return (key);
}

/*
	Extracting the variable name after the dollar sign,
		retrieving the corresponding value
	from the environment variables env_var.
	Returns the expanded value.
	We pass the $ and we check if next char is digit.
		If so, we pass it and return an empty string.
	We get the key and store it in key.
	If there is no key, we return a simple $.
	We get the value of the variable from the environment variables.
	Freeing the key and lasty returnig the value (or NULL if variable not found).
*/

char	*dollar(char **str, t_list *env_var)
{
	int		i;
	char	*key;
	char	*value;

	(*str) += 1;
	if (ft_isnum(**str))
	{
		(*str) += 1;
		return (ft_strdup(""));
	}
	key = get_key(str, &i);
	if (!key)
		return (NULL);
	if (i == 0)
	{
		ft_safe_free(key);
		if (!**str || (*str)[i] == ':' || (*str)[i] == '=' || (*str)[i] == '+')
			return (ft_strdup("$"));
		else
			return (NULL);
	}
	value = get_var(key, env_var);
	free(key);
	return (value);
}
