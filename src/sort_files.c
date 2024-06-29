/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 03:26:05 by bammar            #+#    #+#             */
/*   Updated: 2024/06/30 03:32:46 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Selection sort.
static void    ft_lstsort(t_list **files, int (*cmp)(void *, void *))
{
    t_list  *i;
    t_list  *j;
    t_list  *min;
    void    *tmp;

    i = *files;
    while (i)
    {
        min = i;
        j = i->next;
        while (j)
        {
            if (cmp(j->content, min->content) < 0)
                min = j;
            j = j->next;
        }
        if (min != i)
        {
            tmp = i->content;
            i->content = min->content;
            min->content = tmp;
        }
        i = i->next;
    }
}

static int  compare_alpha(void *a, void *b)
{
    return (ft_strcmp(((t_file *)a)->name, ((t_file *)b)->name));
}

static int  compare_time(void *a, void *b)
{
    return (ft_strcmp(((t_file *)a)->name, ((t_file *)b)->name));
}

void   sort_files(t_list **files, int flags)
{
    if (flags & TIME)
        ft_lstsort(files, compare_time);
    else
        ft_lstsort(files, compare_alpha);
}