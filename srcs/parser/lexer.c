/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:38:09 by cbiteau           #+#    #+#             */
/*   Updated: 2024/04/09 19:25:20 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
	A simple word delimited by special chars.
*/

char	*word(char **str)
{
	int		i;
	char	*word;

	i = 0;
	while ((*str)[i] && !ft_isspace((*str)[i]) && !is_special((*str) + i)
			&& (*str)[i] != '\'' && (*str)[i] != '"' && (*str)[i] != '$'
			&& (*str)[i] != '\\')
		i++;
	word = ft_substr(*str, 0, i);
	(*str) += i;
	return (word);
}

/*
	Takes a linked list of strings and concats its content into a single string.
	Identifying as well the memory to allocate for such an operation.
*/

char	*join_list(t_list *to_cat)
{
	char	*dest;
	t_list	*temp;
	int		to_malloc;

	to_malloc = 0;
	temp = to_cat;
	while (temp && temp->content)
	{
		to_malloc += ft_strlen((char *)temp->content);
		temp = temp->next;
	}
	dest = ft_calloc(to_malloc + 1, sizeof(char));
	if (!dest)
		return (NULL);
	while (to_cat && to_cat->content)
	{
		ft_strcat(dest, (char *)to_cat->content);
		to_cat = to_cat->next;
	}
	return (dest);
}

/*
	Adding a special string token to the linked list of tokens.
	Managing it to place back to the list.
*/

static t_bool	add_special_str(t_list **word_list, char **str, int *error)
{
	char	*special_str;
	t_list	*elem;

	special_str = special(str);
	if (!special_str)
	{
		*error = LOG_ERROR;
		return (false);
	}
	elem = ft_lstnew(special_str);
	if (!elem)
	{
		free(special_str);
		*error = LOG_ERROR;
		return (false);
	}
	ft_lstadd_back(word_list, elem);
	return (true);
}

/*
	In the string input,
		we check if we tokenize only up to the next semicolon (false)
			or pipes and semicolons only (true).
	We check if there is a special char (redirection symbols),
		and we add the special char to the word_list.
	Else, we simply create the word as it is.
*/

t_list	*tokenize(char **str, int *error, t_list *env_var, t_bool just_pipes)
{
	t_list	*word_list;
	t_list	*word_tokens;

	word_list = NULL;
	while (**str && (!just_pipes || **str != ';'))
	{
		if (is_special(*str))
			add_special_str(&word_list, str, error);
		else
		{
			word_tokens = make_word(str, error, env_var, just_pipes);
			ft_lstcat(&word_list, word_tokens);
			ft_lstclear(&word_tokens, ft_nofree);
		}
		if (*error == LOG_ERROR)
		{
			ft_lstclear(&word_list, ft_safe_free);
			break ;
		}
		while (ft_isspace(**str))
			(*str)++;
	}
	if (**str == ';')
		(*str)++;
	return (word_list);
}

t_list	*tokenize_all(char *str, int *error, t_list *env_var)
{
	*error = NO_ERROR;
	return (tokenize(&str, error, env_var, false));
}
