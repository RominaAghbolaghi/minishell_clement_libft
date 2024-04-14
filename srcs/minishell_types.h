/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:30:26 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:30:30 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPES_H

# define MINISHELL_TYPES_H

# include "minishell.h"

extern int	g_unset;
/*
** size: the actual size of the buffer.
** position: ths position of the cursor from the back ____[]__ position = 2.
** buff: string allocated on the heap null terminated.
** escape_id: The id of the escape sequence. Generated by get_escape_id;
** manage_history: true of false, tell if the history should be managed
*/

typedef struct s_buffer
{
	int		size;
	int		pos_before_endl;
	char	*buff;
	int		escape_id;
	char	*status;
	int		history_lvl;
	t_bool	error;
	char	*clipboard;
}				t_buffer;

typedef struct s_redir
{
	int		type;
	char	*file;
}				t_redir;

typedef struct s_command
{
	char	*name;
	char	*cmd;
	t_bool	is_set;
	t_list	*args;
	t_list	*redirs;
	int		backup[2];
}				t_command;

typedef struct s_var
{
	char	*key;
	char	*data;
}			t_var;

typedef int	t_tube[2];

typedef struct s_append
{
	t_bool	start;
	t_bool	end;
	t_bool	dollar_error;
	t_bool	just_pipes;
}				t_append;

typedef struct s_child_data
{
	t_command	*command;
	t_tube		*tube_list;
	int			fork_n;
	int			forks_running;
	t_list		**env_var;
}				t_child_data;

#endif
