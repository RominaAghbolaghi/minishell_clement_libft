/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:33 by cbiteau           #+#    #+#             */
/*   Updated: 2024/04/08 19:27:05 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Gere le comportement des double quote s'arrete
** en cas de char special
*/

char	*double_quote(char **str)
{
	int		i;
	char	*token;

	i = 0;
	token = NULL;
	while ((*str)[i] && (*str)[i] != '"' && (*str)[i] != '$'
			&& (*str)[i] != '\\')
		i++;
	token = ft_substr(*str, 0, i);
	(*str) += i;
	return (token);
}

static char	*dollar2(char **str, t_list *env_var)
{
	int		i;
	char	*key;
	char	*value;

	(*str) += 1;
	if (**str == '"')
		return (ft_strdup("$"));
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
		return (ft_strdup("$"));
	}
	value = get_var(key, env_var);
	free(key);
	return (value);
}

static t_bool	add_db_quote_word(char **str, t_list *env_var, t_list **to_join)
{
	char	*word_str;
	t_list	*elem;

	if (**str == '$')
		word_str = dollar2(str, env_var);
	else if (**str == '\\')
		word_str = backslash_double_quote(str);
	else
		word_str = double_quote(str);
	if (word_str)
		elem = ft_lstnew(word_str);
	if (!word_str || !elem)
	{
		ft_safe_free(word_str);
		ft_lstclear(to_join, ft_safe_free);
		return (false);
	}
	ft_lstadd_back(to_join, elem);
	return (true);
}

/*
** Retourne le str de l'interieur des double quote
** EX "Hello $USER you have 10\$" -> "Hello tmatis you have 10$"
*/

char	*make_double_quote(char **str, int *error, t_list *env_var)
{
	t_list	*to_join;
	char	*dest;

	(*str) += 1;
	to_join = NULL;
	while (**str && **str != '"')
		if (!add_db_quote_word(str, env_var, &to_join))
			return (NULL);
	dest = join_list(to_join);
	ft_lstclear(&to_join, ft_safe_free);
	if (!dest)
		return (NULL);
	if (**str != '"')
	{
		free(dest);
		*error = DB_QUOTE_ERR;
		return (NULL);
	}
	(*str) += 1;
	return (dest);
}
