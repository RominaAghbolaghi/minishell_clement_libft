/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:38:39 by cbiteau           #+#    #+#             */
/*   Updated: 2024/04/09 13:20:56 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
	Returns special char's value else 0.
*/

int	is_special(char *str)
{
	int		strlen;

	strlen = ft_strlen(str);
	if (strlen >= 2 && !ft_memcmp(str, ">>", 2))
		return (APPEND);
	if (*str == '>')
		return (REDIR_OUT);
	if (*str == '<')
		return (REDIR_IN);
	if (*str == '|')
		return (PIPE);
	if (*str == ';')
		return (SEMICOLON);
	return (0);
}

// int	is_special(char *str)
// {
// 	int		strlen;

// 	strlen = ft_strlen(str);
// 	if (strlen >= 2 && !ft_memcmp(str, ">>", 2))
// 		return (APPEND);
// 	if (*str == '>')
// 		return (REDIR_OUT);
// 	if (*str == '<')
// 		return (REDIR_IN);
// 	if (*str == '|')
// 		return (PIPE);
// 	if (*str == ';')
// 		return (SEMICOLON);
// 	if (*str == '&')
// 		return (ANDD);
// 	return (0);
// }

/*
	Read an escpae after tokenization.
*/

int	escape_control(char *str)
{
	if (*str == ESC)
		return (is_special(str + 1));
	else
		return (0);
}

void	set_status_env(t_list **env_var, int status)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (!status_str)
	{
		ft_putstr_fd("Minishell: cannot set status\n", STDERR_FILENO);
		return ;
	}
	edit_var(env_var, "?", status_str);
	free(status_str);
}

/*
	Detects chars specials "; | >> > <" : 
	places a \33 (escape) in fornt of user input to diff
*/

char	*special(char **str)
{
	char	*token;

	token = ft_calloc(4, sizeof (char));
	if (!token)
		return (NULL);
	token[0] = ESC;
	if (is_special(*str) == APPEND)
	{
		ft_memcpy(token + 1, *str, 2);
		(*str) += 2;
	}
	else
	{
		ft_memcpy(token + 1, *str, 1);
		(*str) += 1;
	}
	return (token);
}
