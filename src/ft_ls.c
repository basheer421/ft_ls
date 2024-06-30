/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:48:57 by bammar            #+#    #+#             */
/*   Updated: 2024/06/30 04:20:04 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * Logic for ls:
 * 
 * 1. Go through current dir and store the files and mark dirs
 * 2. Now you have a list of files and if they are dirs
 * 3. Sort the list of files with the flags or default (alphabetic)
 * 4. Print based on flags the files of the dir from the given list. If the -R flag is given, then
 * 	after printing the files go through the dir ones and apply the same function to them.
 * 	Store visited dirs to prevent errors.
 */

/**
 * Return a linked list of t_files from the current path
 */
static t_list	*get_files(char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*files;
	t_file			*file;
	t_list			*ret;

	dir = opendir(path);
	if (!dir)
		return (perror("ft_ls"), NULL);
	files = ft_lstnew(NULL);
	entry = readdir(dir);
	while (entry)
	{
		file = ft_malloc(sizeof(t_file));
		file->name = ft_strdup(entry->d_name);
		if (!file->name)
			exit(EXIT_FAILURE);
		file->is_dir = entry->d_type == DT_DIR;
		ft_lstadd_back(&files, ft_lstnew(file));
		entry = readdir(dir);
	}
	closedir(dir);
	ret = files->next;
	ft_lstdelone(files, destroy_file);
	return (ret);
}

int	ls(char *path, int flags, int print_dir_name, int origin)
{
	t_list	*files;
	t_list	*current;
	t_file	*file;

	files = get_files(path);
	if (!files)
		return (ft_lstclear(&files, destroy_file), free(path), 1);
	sort_files(&files, flags);
	if (!origin && print_dir_name)
		ft_printf("\n");
	if (print_dir_name && path[0])
		ft_printf("%s:\n", path);
	current = files;
	while (current)
	{
		file = current->content;
		if (file->name[0] != '.' || (flags & ALL))
			ft_printf("%s", file->name);
		if (current->next && (file->name[0] != '.' || (flags & ALL)))
			ft_printf("  ");
		else if (file->name[0] != '.' || (flags & ALL))
			ft_printf("\n");
		current = current->next;
	}
	if (flags & RECURSIVE)
	{
		current = files;
		while (current)
		{
			file = current->content;
			if (file->is_dir && has_recursion(file->name, flags))
				ls(join_path(path, file->name), flags, 1, 0);
			current = current->next;
		}
	}
	return (ft_lstclear(&files, destroy_file), free(path), 0);
}

static int	init_args(t_ls_args *args)
{
	ft_bzero(args, sizeof(t_ls_args));
	args->files = ft_dqnew();
	if (!args->files)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_ls_args	args;
	int			ret;

	if (!init_args(&args))
		return (ft_putendl_fd("ft_ls: No memory", 2), EXIT_FAILURE);
	ret = 0;
	if (argc == 1)
	{
		ls(ft_strdup("."), 0, 0, 1);
		return (ft_dqdel(args.files, 0), 0);
	}
	if (parse(argc, argv, &args) < 0)
		return (ft_dqdel(args.files, free), 1);
	t_dlist *current = args.files->head;
	while (current) {
		if (ls(ft_strdup(current->content), args.flags, (ft_lstsize((t_list *)current) > 1)
			|| (args.flags & RECURSIVE), 1))
			ret = 2;
		current = current->next;
	}
	return (ft_dqdel(args.files, free), ret);
}
