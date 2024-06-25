/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dqcontains.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:18:52 by bammar            #+#    #+#             */
/*   Updated: 2024/06/25 04:08:25 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dq.h"

int	ft_dqcontains(t_dq *dq, char *item)
{
	t_dlist	*node;

	node = dq->head;
	while (node)
	{
		if (ft_strncmp(node->content, item, ft_strlen(item)) == 0)
			return (1);
		node = node->next;
	}
	return (0);
}
