/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8_encode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:06:43 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:06:44 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This function transform codepoint c to 1-4 char.
** return the number of generated char
*/

int	ft_utf8_encode(int c, char *buff)
{
	int		i;

	i = 0;
	if (c < 0x80)
		buff[i++] = c;
	else if (c < 0x0800)
	{
		buff[i++] = ((c >> 6) & 0x1F) | 0xC0;
		buff[i++] = ((c >> 0) & 0x3F) | 0x80;
	}
	else if (c < 0x010000)
	{
		buff[i++] = ((c >> 12) & 0x0F) | 0xE0;
		buff[i++] = ((c >> 6) & 0x3F) | 0x80;
		buff[i++] = ((c >> 0) & 0x3F) | 0x80;
	}
	else if (c < 0x110000)
	{
		buff[i++] = ((c >> 18) & 0x07) | 0xF0;
		buff[i++] = ((c >> 12) & 0x3F) | 0x80;
		buff[i++] = ((c >> 6) & 0x3F) | 0x80;
		buff[i++] = ((c >> 0) & 0x3F) | 0x80;
	}
	return (i);
}
