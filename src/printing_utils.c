/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 02:32:11 by bammar            #+#    #+#             */
/*   Updated: 2024/07/02 02:37:04 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file(t_file *file, int flags, int is_last, int *max_len)
{
	if (file->name[0] != '.' || (flags & ALL))
	{
		if (flags & LONG)
			print_long(file, max_len);
		else
			ft_printf("%s", file->name);
	}
	if (!is_last && (file->name[0] != '.' || (flags & ALL)))
	{
		if (flags & LONG)
			ft_printf("\n");
		else
			ft_printf("  ");
	}
	else if (file->name[0] != '.' || (flags & ALL))
	{
		ft_printf("\n");
	}
}

unsigned int	get_total_blocks(t_list *files, int flags)
{
	unsigned int	total;
	t_list			*current;
	t_file			*file;

	total = 0;
	current = files;
	while (current)
	{
		file = current->content;
		if (file->name[0] != '.' || flags & ALL)
			total += file->stats.st_blocks;
		current = current->next;
	}
	return (total / 2);
}

static int	is_single_file(t_list *files)
{
	if (ft_lstsize(files) == 1)
	{
		if (!S_ISDIR(((t_file *)files->content)->stats.st_mode))
			return (1);
	}
	return (0);
}

int	handle_single_file(t_list *files, int flags, int *max_len, char *path)
{
	t_file	*file;

	if (is_single_file(files))
	{
		file = files->content;
		print_file(file, flags, 1, max_len);
		return (ft_lstclear(&files, destroy_file), free(path), 1);
	}
	return (0);
}
