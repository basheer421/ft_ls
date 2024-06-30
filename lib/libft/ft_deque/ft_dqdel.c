/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dqdel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:17:37 by bammar            #+#    #+#             */
/*   Updated: 2024/06/30 04:09:40 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dq.h"

void	ft_dqdel(t_dq *lst, void (*del)(void *))
{
	t_dlist	*node;
	t_dlist	*tmp;

	node = lst->head;
	while (node)
	{
		tmp = node;
		node = node->next;
		if (del)
			del(tmp->content);
		free(tmp);
	}
	free(lst);
}
