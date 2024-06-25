/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dqadd_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:52:28 by bammar            #+#    #+#             */
/*   Updated: 2022/11/07 23:00:38 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dq.h"

void	ft_dqadd_first(t_dq *lst, t_dlist *new)
{
	if (!lst)
		return ;
	if (!lst->tail)
	{
		lst->head = new;
		lst->tail = new;
		return ;
	}
	new->next = lst->head;
	lst->head->prev = new;
	lst->head = new;
}
