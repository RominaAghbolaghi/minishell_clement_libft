/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:23:55 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:24:01 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_H

# define PUT_H
# include "../string/string.h"

void	ft_putchar_fd(int c, int fd);
void	ft_putwstr_fd(int *wstr, int fd);
void	ft_putstr(char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(int c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnl(char *str);
void	ft_putprintable(char *str);

#endif
