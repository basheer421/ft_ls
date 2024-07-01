/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_max_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:50:57 by bammar            #+#    #+#             */
/*   Updated: 2024/07/01 18:59:28 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int  get_len(long n)
{
    int	len;

    len = 0;
    while (n)
    {
        n /= 10;
        len++;
    }
    return (len);
}

int get_max_len(t_list *files)
{
    int		max_len;
    int		len;
    t_file	*file;

    max_len = 0;
    while (files)
    {
        file = files->content;
        len = get_len(file->stats.st_size);
        if (len > max_len)
            max_len = len;
        files = files->next;
    }
    return (max_len);
}
