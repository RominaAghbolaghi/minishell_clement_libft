/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstring.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:28:18 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:28:19 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WSTRING_H

# define WSTRING_H

# include <string.h>

int		ft_wstr_strlen(int *wstr);
size_t	ft_wstrlen(int *wstr);
size_t	ft_wstrnlen(const int *s, size_t maxlen);
size_t	ft_wstrtostr(char *dest, int *wsrc);
char	*ft_wstrtostr_malloc(int *wsrc);

#endif
