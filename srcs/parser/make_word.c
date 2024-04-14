/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:38:30 by cbiteau           #+#    #+#             */
/*   Updated: 2024/04/08 18:29:13 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
	Handling the process of having a dollar sign.
		It manages the concat and handling
			of tokens before, between, and after variable expansions.
	If no dolloar token and if previous dollar error occured, we exit error.
	Else if no dollar token, we exit.
	If there is a start flag, we attempt ot append a dollar token at the start.
	If there is a dollar_token and a to_join list,
		we attempt to add joint tokens using add_joint_tokens.
	If there is an end flag and dollar_tokens,
		we attempt to append a dollar token at the end.
	Then, we set the flags to true.
	We must concatenate the dollar tokens
*/

static int	handle_dollar(t_list **dollar_tokens, t_list **tokens,
								t_list **to_join, t_append *append)
{
	if (!*dollar_tokens && append->dollar_error)
	{
		ft_lstclear(to_join, ft_safe_free);
		ft_lstclear(tokens, ft_safe_free);
		return (LOG_ERROR);
	}
	else if (!*dollar_tokens)
		return (NO_ERROR);
	if (append->start)
		if (!append_dollar_token(dollar_tokens, tokens, to_join, START))
			return (LOG_ERROR);
	if (*dollar_tokens && *to_join)
		if (!add_joint_tokens(dollar_tokens, tokens, to_join))
			return (LOG_ERROR);
	if (append->end && *dollar_tokens)
		if (!append_dollar_token(dollar_tokens, tokens, to_join, END))
			return (LOG_ERROR);
	append->start = true;
	append->end = true;
	ft_lstcat(tokens, *dollar_tokens);
	ft_lstclear(dollar_tokens, ft_nofree);
	return (NO_ERROR);
}

/*
	Initiaize values here to optimize line count.
*/

static void	init_value(t_append *append, t_list **dollar_tokens,
							t_list **tokens, t_list **to_join)
{
	append->start = true;
	append->end = true;
	append->dollar_error = false;
	*dollar_tokens = NULL;
	*tokens = NULL;
	*to_join = NULL;
}

/*
	Responsible for adding a word to the tokens lsit.
	We check the type of quoting or escaping and process accordingly.
	We check if element by word string was successfully created.
	if elem or word_str failed, we free and exit error.
	Else, we add the list element to the to_join list.
*/

static t_bool	add_word(char **str, int *error,
							t_list *env_var, t_list **to_join)
{
	char	*word_str;
	t_list	*elem;

	if (**str == '"')
		word_str = make_double_quote(str, error, env_var);
	else if (**str == '\'')
		word_str = single_quote(str, error);
	else if (**str == '\\')
		word_str = backslash(str);
	else
		word_str = word(str);
	if (word_str)
		elem = ft_lstnew(word_str);
	if (!word_str || !elem)
	{
		ft_safe_free(word_str);
		ft_lstclear(to_join, ft_safe_free);
		if (*error == NO_ERROR)
			*error = LOG_ERROR;
		return (false);
	}
	ft_lstadd_back(to_join, elem);
	return (true);
}

/*
	Creating a list of tokens representing a word for bash.
	We iterate through the input until next space or end of string.
	If the current *str is a dollar sign, we call the dollar_tok,
		then we handle the dollar sign expansion.
	Else if it is not, add the word to the join+list.
		In case of error, oviously clear the list and free for safety.
		Break.
	If there are tokens to joinm add joint tokens to the tokens list.
	Return the tokens list.
	
*/

t_list	*make_word(char **str, int *error, t_list *env_var, t_bool just_pipes)
{
	t_append	append;
	t_list		*dollar_tokens;
	t_list		*tokens;
	t_list		*to_join;

	init_value(&append, &dollar_tokens, &tokens, &to_join);
	append.just_pipes = just_pipes;
	while (**str && !ft_isspace(**str) && !is_special(*str))
	{
		if (**str == '$')
		{
			dollar_tokens = dollar_tokenize(str, &append, error, env_var);
			*error = handle_dollar(&dollar_tokens, &tokens, &to_join, &append);
			if (*error != NO_ERROR)
				break ;
		}
		else if (!add_word(str, error, env_var, &to_join))
		{
			ft_lstclear(&tokens, ft_safe_free);
			break ;
		}
	}
	if (to_join)
		add_joint_tokens(&dollar_tokens, &tokens, &to_join);
	return (tokens);
}
