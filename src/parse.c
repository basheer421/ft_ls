/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:26:43 by bammar            #+#    #+#             */
/*   Updated: 2024/07/02 03:04:05 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*make_file(char *name)
{
	t_list	*file_node;
	t_file	*file;

	file_node = ft_lstnew(NULL);
	file_node->content = ft_malloc(sizeof(t_file));
	file = file_node->content;
	file->name = name;
	if (lstat(name, &file->stats) == -1)
	{
		perror("ft_ls");
		file->name = "";
	}
	return (file_node);
}

static void	check_empty(t_list **files)
{
	if (*files == NULL)
		*files = make_file(".");
}

int	parse(int argc, char **argv, t_ls_args *args)
{
	int		i;
	int		flags;

	i = 0;
	flags = 0;
	args->files = NULL;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			flags |= parse_flags(argv[i] + 1);
			if (flags == -1)
				return (ft_putendl_fd("ft_ls: Bad Flag", 2), -1);
		}
		else
		{
			if (args->files == NULL)
				args->files = make_file(argv[i]);
			else
				ft_lstadd_back(&(args->files), make_file(argv[i]));
		}
	}
	check_empty(&(args->files));
	args->flags = flags;
	return (sort_files(&(args->files), args->flags), 0);
}
