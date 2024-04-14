/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:08:53 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:08:54 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}

void	ft_lstremove_first(t_list **alst, void (*del)(void*))
{
	t_list	*temp;

	temp = (*alst)->next;
	ft_lstdelone(*alst, del);
	*alst = temp;
}
