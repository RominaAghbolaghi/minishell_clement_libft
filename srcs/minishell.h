/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:30:15 by cbiteau           #+#    #+#             */
/*   Updated: 2024/04/04 21:33:16 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <errno.h>
# include <limits.h>
# include "../libft/libft.h"
# include "minishell_types.h"
# include "builtin/builtin.h"
# include "parser/parser.h"
# include "input_manager/input_manager.h"
# include "exec/exec.h"

# define BLUE_COLOR "\033[1;36m"
# define RESET_BLUE_COLOR "\033[0m"
# define PURPLE_COLOR "\x1b[35m"
# define RESET_PURPLE_COLOR "\x1b[0m"

# define NO_ERROR		-1
# define ENV_VAR_ERROR	"Error while creating an environment variable"
# ifdef __APPLE__
#  define LS_COLOR "-G"
# else
#  define LS_COLOR "--color"
# endif

int				minishell(t_list **env_var, t_list *history);
int             generic_error(char *error, char *path);
void			write_error(int error_number);
char			*search_var(t_list *var_list, char *key);
void			free_var(void *mem);
t_bool			edit_var(t_list **var_list, char *key, char *value);
void			*load_var_error(char *message, t_var *var_to_free, void *ret);
t_var			*create_var(char *str);

#endif
