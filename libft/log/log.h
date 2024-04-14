/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:08:17 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:08:18 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H

# define LOG_H
# include "../libft.h"

void	ft_log_warn(char *log);
void	ft_log_info(char *log);
void	ft_log_error(char *log);
void	ft_log_task(char *log);
void	ft_log_ok(t_bool b);

#endif
