/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dqdel_last.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 23:01:22 by bammar            #+#    #+#             */
/*   Updated: 2022/11/12 20:39:53 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dq.h"

void	ft_dqdel_last(t_dq *lst)
{
	t_dlist	*temp;

	if (!lst || !lst->tail)
		return ;
	temp = lst->tail;
	lst->tail = lst->tail->prev;
	if (lst->tail)
		lst->tail->next = NULL;
	else
		lst->head = NULL;
	free((void *)temp);
}
