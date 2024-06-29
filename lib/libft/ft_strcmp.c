/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 23:01:35 by bammar            #+#    #+#             */
/*   Updated: 2024/06/29 23:04:47 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
    size_t  s1_len;
    size_t  s2_len;

    s1_len = ft_strlen(s1);
    s2_len = ft_strlen(s2);
    if (s1_len > s2_len)
        return (ft_strncmp(s1, s2, s1_len));
    return (ft_strncmp(s1, s2, s2_len));
}
