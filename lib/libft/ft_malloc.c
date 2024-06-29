/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 22:49:01 by bammar            #+#    #+#             */
/*   Updated: 2024/06/29 22:50:57 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_malloc(size_t size)
{
    void    *ptr;

    ptr = malloc(size);
    if (!ptr)
        exit(EXIT_FAILURE);
    return (ptr);
}
