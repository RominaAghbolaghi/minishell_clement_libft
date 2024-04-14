/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_detector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:52 by cbiteau           #+#    #+#             */
/*   Updated: 2024/04/11 19:51:00 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/stat.h>

static int	set_error(int n, int *error)
{
	*error = n;
	return (1);
}

static int	get_errno(int special_id)
{
	return (special_id + 2);
}

/*
	Checking for any unexpected errors related
		to special charatcers in a list of tokens.
	We get the id of the special character. Get the next if there is one too.
	Checking for pipe at the end of the tokens list.
	Checking redirection without a following token,
		or followed by another special char.
	Pipe or semicol followed by a second one.
	report any error.
	ese return 0.

*/

static int	error_unexpected(t_list *tokens, int *error)
{
	int		special_id;
	int		special_id_next;

	special_id = escape_control(tokens->content);
	if (tokens->next)
		special_id_next = escape_control(tokens->next->content);
	if ((special_id == PIPE && !tokens->next))
		return (set_error(get_errno(special_id), error));
	if ((special_id == REDIR_OUT || special_id == REDIR_IN
			|| special_id == APPEND) && !tokens->next)
		return (set_error(NL_ERR, error));
	if ((special_id == REDIR_OUT || special_id == REDIR_IN
			|| special_id == APPEND) && tokens->next && special_id_next)
		return (set_error(get_errno(special_id_next), error));
	if ((special_id == PIPE || special_id == SEMICOLON) && tokens->next
		&& (special_id_next == PIPE || special_id_next == SEMICOLON))
		return (set_error(get_errno(special_id_next), error));
	return (0);
}

/*
	Handling potential errors in a linked list of tokens.
	If no previous errors have occured, we may proceed.
	If semicolon at the beginning of the list,
		set an error and handles the error output and exit.
	Iterate through the tokens and check for unexpected errors.
*/

void	error_detector(t_list *tokens, int *error, t_list **env_var)
{
	if (*error != NO_ERROR)
	{
		write_error(*error);
		set_status_env(env_var, 2);
		return ;
	}
	if (tokens && (escape_control(tokens->content) == SEMICOLON
			|| escape_control(tokens->content) == PIPE))
	{
		*error = get_errno(escape_control(tokens->content));
		write_error(*error);
		set_status_env(env_var, 2);
		return ;
	}
	while (tokens && tokens->content)
	{
		if (error_unexpected(tokens, error))
		{
			write_error(*error);
			set_status_env(env_var, 2);
			return ;
		}
		tokens = tokens->next;
	}
}

/////////////////////// old version ////////////////////////////////////
// static int	error_unexpected(t_list *tokens, int *error)
// {
// 	int		special_id;
// 	int		special_id_next;

// 	special_id = escape_control(tokens->content);
// 	if (tokens->next)
// 		special_id_next = escape_control(tokens->next->content);
// 	if ((special_id == PIPE && !tokens->next))
//		return (set_error(EOL_ERR, error));
// 	if ((special_id == REDIR_OUT || special_id == REDIR_IN
// 			|| special_id == APPEND) && !tokens->next)
// 		return (set_error(NL_ERR, error));
// 	if ((special_id == REDIR_OUT || special_id == REDIR_IN
// 			|| special_id == APPEND) && tokens->next && special_id_next)
// 		return (set_error(get_errno(special_id_next), error));
// 	if ((special_id == PIPE || special_id == SEMICOLON) && tokens->next
// 		&& (special_id_next == PIPE || special_id_next == SEMICOLON))
// 		return (set_error(get_errno(special_id_next), error));
// 	return (0);
// }

// void	error_detector(t_list *tokens, int *error, t_list **env_var)
// {
// 	if (*error != NO_ERROR)
// 	{
// 		write_error(*error);
// 		set_status_env(env_var, 2);
// 		return ;
// 	}
//	if (tokens && escape_control(tokens->content) == SEMICOLON)
// 	{
// 		*error = get_errno(SEMICOLON);
// 		write_error(*error);
// 		set_status_env(env_var, 2);
// 		return ;
// 	}
// 	while (tokens && tokens->content)
// 	{
// 		if (error_unexpected(tokens, error))
// 		{
// 			write_error(*error);
// 			set_status_env(env_var, 2);
// 			return ;
// 		}
// 		tokens = tokens->next;
// 	}
// } 
//////////////////////// with error_detector2.c///////////////////////////////
// static int	error_unexpected(t_list *tokens, int *error, t_list **env_var)
// {
// 	int		special_id;
// 	int		special_id_next;

// 	special_id = escape_control(tokens->content);
// 	if (tokens->next)
// 		special_id_next = escape_control(tokens->next->content);
// 	if ((special_id == PIPE && !tokens->next)
// 		|| (special_id == PIPE && tokens->next
// 			&& !find_bin2((char *)(tokens->next->content), *env_var)))
// 		return (set_error(get_errno(special_id), error));
// 	if ((special_id == REDIR_OUT || special_id == REDIR_IN
// 			|| special_id == APPEND) && !tokens->next)
// 		return (set_error(NL_ERR, error));
// 	if ((special_id == REDIR_OUT || special_id == REDIR_IN
// 			|| special_id == APPEND) && tokens->next && special_id_next)
// 		return (set_error(get_errno(special_id_next), error));
// 	if ((special_id == PIPE || special_id == SEMICOLON) && tokens->next
// 		&& (special_id_next == PIPE || special_id_next == SEMICOLON))
// 		return (set_error(get_errno(special_id_next), error));
// 	return (0);
// }

// void	error_detector(t_list *tokens, int *error, t_list **env_var)
// {
// 	if (*error != NO_ERROR)
// 	{
// 		write_error(*error);
// 		set_status_env(env_var, 2);
// 		return ;
// 	}
//	// if (tokens && (escape_control(tokens->content) == SEMICOLON
//	// 		|| escape_control(tokens->content) == PIPE))
// 	// if (tokens && escape_control(tokens->content) == SEMICOLON)
// 	{
// 		*error = get_errno(escape_control(tokens->content));
// 		write_error(*error);
// 		set_status_env(env_var, 2);
// 		return ;
// 	}
// 	while (tokens && tokens->content)
// 	{
// 		if (error_unexpected(tokens, error, env_var))
// 		{
// 			write_error(*error);
// 			set_status_env(env_var, 2);
// 			return ;
// 		}
// 		tokens = tokens->next;
// 	}
// }
