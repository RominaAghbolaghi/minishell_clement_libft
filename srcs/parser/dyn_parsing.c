/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:40 by cbiteau           #+#    #+#             */
/*   Updated: 2024/04/09 19:41:37 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Cree une liste de commande execute simultanement relier par des pipes
*/

static t_list	*pipes_commands(t_list *word_list, t_list *env_var)
{
	t_list		*pipes_list;
	int			special_id;
	t_command	*command;
	t_list		*elem;

	pipes_list = NULL;
	while (word_list)
	{
		special_id = escape_control(word_list->content);
		if (special_id == PIPE)
			word_list = word_list->next;
		if (special_id == SEMICOLON || !word_list)
			break ;
		command = get_command(&word_list, env_var);
		if (command)
			elem = ft_lstnew(command);
		if (!command || !elem)
		{
			ft_safe_free(command);
			ft_lstclear(&pipes_list, free_command);
			return (NULL);
		}
		ft_lstadd_back(&pipes_list, elem);
	}
	return (pipes_list);
}

static t_list	*get_next_pipes(char **str, int *error, t_list **env_var)
{
	t_list	*token_list;
	t_list	*pipes_list;

	token_list = tokenize(str, error, *env_var, true);
	if (*error != NO_ERROR)
	{
		write_error(*error);
		set_status_env(env_var, 2);
		return (NULL);
	}
	pipes_list = pipes_commands(token_list, *env_var);
	ft_lstclear(&token_list, ft_safe_free);
	if (!pipes_list && token_list)
	{
		ft_log_error(strerror(errno));
		set_status_env(env_var, 2);
		return (NULL);
	}
	return (pipes_list);
}

static int	change_status(t_list **env_var, t_list *pipes_list, char *str,
					int error)
{
	if (!pipes_list && (!*str || error != NO_ERROR))
	{
		set_status_env(env_var, 0);
		return (0);
	}
	return (1);
}

/*
	Calling the tokenisor and parse the commands,
	and call the execution.
	Firstly, we tokenize the input line into a list of words.
	Secondly, We check for errors in tokenization.
	Thirdly, We clear the word_list and return 0 if error was detected.
	Fourthly, in the tring given, we identify the pipes.
	Fifthly, if pipes were indeed found, we execute in the pipes_list 
	the commands.
	Sixthly, we clear the pipes_list
		and give to return_value the value if there is one.
*/
int	exec_line(char *str, t_list **env_var)
{
	t_list		*word_list;
	t_list		*pipes_list;
	int			error;
	int			return_value;

	word_list = tokenize_all(str, &error, *env_var);
	error_detector(word_list, &error, env_var);
	ft_lstclear(&word_list, free);
	if (error != NO_ERROR)
		return (0);
	while (*str)
	{
		return_value = 0;
		pipes_list = get_next_pipes(&str, &error, env_var);
		if (!change_status(env_var, pipes_list, str, error))
			return (0);
		if (pipes_list)
			return_value = exec(pipes_list, env_var);
		ft_lstclear(&pipes_list, free_command);
		if (return_value)
			return (return_value);
	}
	return (0);
}
