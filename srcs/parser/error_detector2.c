/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_detector2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:24:20 by romina            #+#    #+#             */
/*   Updated: 2024/04/11 19:51:48 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/stat.h>

static t_bool	file_exist2(char *path)
{
	struct stat	buffer;
	int			exist;

	exist = stat(path, &buffer);
	if (exist == 0)
		return (true);
	else
		return (false);
}

static t_bool	search_path2(char **paths, char *command)
{
	int		i;
	char	*to_check;

	i = 0;
	while (paths[i])
	{
		to_check = ft_calloc(ft_strlen(paths[i])
				+ ft_strlen(command) + 2, sizeof(char));
		if (!to_check)
			return (false);
		ft_strcat(to_check, paths[i]);
		ft_strcat(to_check, "/");
		ft_strcat(to_check, command);
		if (file_exist2(to_check))
		{
			free(to_check);
			return (true);
		}
		free(to_check);
		i++;
	}
	return (false);
}

t_bool	find_bin2(char *command, t_list *env_var)
{
	char	**paths;

	paths = ft_split(search_var(env_var, "PATH"), ':');
	if (!paths && search_var(env_var, "PATH") != NULL)
		return (false);
	if (!paths || !*paths)
	{
		free_table(&paths);
		return (command != NULL);
	}
	if (!search_path2(paths, command))
	{
		free_table(&paths);
		return (false);
	}
	free_table(&paths);
	return (true);
}
