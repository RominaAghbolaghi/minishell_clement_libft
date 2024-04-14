/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_one_if_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:09:51 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:09:52 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	ft_lstremove_one_if(t_list **alst, void *data_ref,
									int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*current;
	t_list	*tmp_prev;

	current = *alst;
	tmp_prev = NULL;
	while (current != NULL)
	{
		if ((*cmp)(current->content, data_ref) == 0)
		{
			if (free_fct != NULL)
				(*free_fct)(current->content);
			if (tmp_prev == NULL)
				*alst = current->next;
			else
				tmp_prev->next = current->next;
			free(current);
			return ;
		}
		tmp_prev = current;
		current = current->next;
	}
}
