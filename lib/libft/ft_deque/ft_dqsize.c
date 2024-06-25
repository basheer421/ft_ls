/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dqsize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:38:52 by bammar            #+#    #+#             */
/*   Updated: 2022/12/19 18:20:06 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dq.h"

size_t	ft_dqsize(t_dq *lst)
{
	t_dlist	*node;
	size_t	size;

	node = lst->head;
	size = 0;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}
