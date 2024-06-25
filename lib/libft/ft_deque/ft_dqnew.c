/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dqnew.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:28:46 by bammar            #+#    #+#             */
/*   Updated: 2024/06/25 04:09:14 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dq.h"

t_dq	*ft_dqnew(void)
{
	t_dq	*dq;

	dq = malloc(sizeof(t_dq));
	if (!dq)
		return (NULL);
	dq -> head = NULL;
	dq -> tail = NULL;
	return (dq);
}
