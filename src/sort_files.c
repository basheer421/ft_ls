/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 03:26:05 by bammar            #+#    #+#             */
/*   Updated: 2024/10/22 16:35:57 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	compare_alpha(void *a, void *b)
{
	return (ft_strcmp(((t_file *)a)->name, ((t_file *)b)->name));
}

/**
 * to use on linux:
 * st_mtimespec.tv_sec st_mtime
 * st_mtimespec.tv_nsec st_mtimensec
 * 
 */
// static int	compare_time(void *a, void *b)
// {
// 	t_file	*file_a;
// 	t_file	*file_b;
// 	time_t	time_a;
// 	time_t	time_b;

// 	file_a = (t_file *)a;
// 	file_b = (t_file *)b;
	
// 	time_a = file_a->stats.st_mtimespec.tv_sec;
// 	time_b = file_b->stats.st_mtimespec.tv_sec;
// 	if (time_a == time_b)
// 	{
// 		time_a = file_a->stats.st_mtimespec.tv_nsec;
// 		time_b = file_b->stats.st_mtimespec.tv_nsec;
// 		if (time_a == time_b)
// 			return (compare_alpha(a, b));
// 		return (time_b - time_a);
// 	}
// 	return (time_b - time_a);
// }

static int	compare_time(void *a, void *b)
{
	t_file	*file_a;
	t_file	*file_b;
	time_t	time_a;
	time_t	time_b;

	file_a = (t_file *)a;
	file_b = (t_file *)b;
	
	time_a = file_a->stats.st_mtime;
	time_b = file_b->stats.st_mtime;
	if (time_a == time_b)
	{
		time_a = file_a->stats.st_mtimensec;
		time_b = file_b->stats.st_mtimensec;
		if (time_a == time_b)
			return (compare_alpha(a, b));
		return (time_b - time_a);
	}
	return (time_b - time_a);
}

// Selection sort.
static void	ft_lstsort(t_list **files, int (*cmp)(void *, void *))
{
	t_list	*i;
	t_list	*j;
	t_list	*min;
	void	*tmp;

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

void	sort_files(t_list **files, int flags)
{
	if (flags & TIME)
		ft_lstsort(files, compare_time);
	else
		ft_lstsort(files, compare_alpha);
	if (!(flags & ALL))

	if (flags & REVERSE)
		rev(files, (flags & ALL));
}
