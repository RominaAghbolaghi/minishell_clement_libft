/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:32:05 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/11 12:05:31 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	get_actualdir(char **actual_dir, t_list *env_var,
						char *var_to_edit)
{
	if (!ft_strcmp(var_to_edit, "OLDPWD") && g_unset == 1)
	{
		*actual_dir = search_var(env_var, "PWD");
		g_unset = 0;
		return (true);
	}
	else if (!getcwd(*actual_dir, BUFFER_SIZE))
	{
		file_error("cannot get PWD", strerror(errno));
		return (false);
	}
	return (true);
}

static t_bool	get_directories(char **old_pwd, char *actual_dir,
										t_list **env_var, char *var_to_edit)
{
	if (old_pwd)
	{
		*old_pwd = ft_strdup(*old_pwd);
		if (!*old_pwd)
		{
			file_error("cannot load OLDPWD", strerror(errno));
			return (false);
		}
	}
	if (!get_actualdir(&actual_dir, *env_var, var_to_edit))
	{
		if (old_pwd)
			free(*old_pwd);
		return (false);
	}
	if (!edit_var2(env_var, var_to_edit, actual_dir))
	{
		if (old_pwd)
			free(*old_pwd);
		return (false);
	}
	return (true);
}

static int	cd_home(t_list **env_var)
{
	char	*home;
	char	actual_dir[BUFFER_SIZE];

	home = search_var(*env_var, "HOME");
	if (!home)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (g_unset == 1)
	{
		if (!edit_var2(env_var, "OLDPWD", search_var(*env_var, "PWD")))
			return (1);
		g_unset = 0;
	}
	else if (!edit_var2(env_var, "OLDPWD", getcwd(actual_dir, BUFFER_SIZE)))
		return (1);
	if (*home && chdir(home) == -1)
		return (generic_error(strerror(errno), home));
	if (!edit_var2(env_var, "PWD", getcwd(actual_dir, BUFFER_SIZE)))
		return (1);
	return (0);
}

static int	cd_oldpwd(t_list **env_var)
{
	char	*old_pwd;
	char	actual_dir[BUFFER_SIZE];

	old_pwd = search_var(*env_var, "OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (!get_directories(&old_pwd, actual_dir, env_var, "OLDPWD"))
		return (1);
	if (chdir(old_pwd) == -1)
	{
		generic_error(strerror(errno), old_pwd);
		free(old_pwd);
		return (1);
	}
	ft_putnl(old_pwd);
	free(old_pwd);
	if (!get_directories(NULL, actual_dir, env_var, "PWD"))
		return (1);
	return (0);
}

int	ft_cd(int argc, char **argv, t_list **env_var)
{
	char	actual_dir[BUFFER_SIZE];

	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "-"))
			return (cd_oldpwd(env_var));
		if (!edit_var2(env_var, "OLDPWD", getcwd(actual_dir, BUFFER_SIZE)))
			return (1);
		if (*argv[1] && chdir(argv[1]) == -1)
			return (generic_error(strerror(errno), argv[1]));
		if (!edit_var2(env_var, "PWD", getcwd(actual_dir, BUFFER_SIZE)))
			return (1);
	}
	else if (argc > 2)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		return (1);
	}
	else if (argc == 1)
		return (cd_home(env_var));
	return (0);
}
