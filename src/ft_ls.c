/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:48:57 by bammar            #+#    #+#             */
/*   Updated: 2024/07/01 23:33:41 by bammar           ###   ########.fr       */
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

static t_list	*try_single_file(char *path)
{
	t_file	*file;

	file = ft_malloc(sizeof(t_file));
	file->name = ft_strdup(path);
	if (!file->name)
		exit(EXIT_FAILURE);
	if (lstat(path, &file->stats) < 0)
		exit(EXIT_FAILURE);
	file->full_path = ft_strdup(path);
	if (!file->full_path)
		exit(EXIT_FAILURE);
	return (ft_lstnew(file));
}

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
	char			*full_path;

	if (!*path)
		return (NULL);
	dir = opendir(path);
	if (!dir)
		return (try_single_file(path));
	files = ft_lstnew(NULL);
	entry = readdir(dir);
	while (entry)
	{
		file = ft_malloc(sizeof(t_file));
		file->name = ft_strdup(entry->d_name);
		if (!file->name)
			exit(EXIT_FAILURE);
		full_path = join_path(path, file->name);
		if (lstat(full_path, &file->stats) < 0)
			exit(EXIT_FAILURE);
		file->full_path = full_path;
		ft_lstadd_back(&files, ft_lstnew(file));
		entry = readdir(dir);
	}
	closedir(dir);
	ret = files->next;
	ft_lstdelone(files, destroy_file);
	return (ret);
}


void	print_file(t_file *file, int flags, int is_last, int max_len)
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

static unsigned int	get_total_blocks(t_list *files)
{
	unsigned int	total;
	t_list			*current;
	t_file			*file;

	total = 0;
	current = files;
	while (current)
	{
		file = current->content;
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

int	ls(char *path, int flags, int print_dir_name, int origin, int ret)
{
	t_list	*files;
	t_list	*current;
	t_file	*file;
	int		max_len;

	files = get_files(path);
	if (!files)
		return (free(path), 2);
	max_len = get_max_len(files);
	sort_files(&files, flags);
	if (!origin && print_dir_name)
		ft_printf("\n");
	if (is_single_file(files))
	{
		file = files->content;
		print_file(file, flags, 1, max_len);
		return (ft_lstclear(&files, destroy_file), free(path), ret);
	}
	if (print_dir_name)
		ft_printf("%s:\n", path);
	if ((flags & LONG))
		ft_printf("total %u\n", get_total_blocks(files));
	current = files;
	while (current)
	{
		file = current->content;
		print_file(file, flags, !current->next, max_len);
		current = current->next;
	}
	if (flags & RECURSIVE)
	{
		current = files;
		while (current)
		{
			file = current->content;
			if (S_ISDIR(file->stats.st_mode) && has_recursion(file->name, flags))
				ret = ls(join_path(path, file->name), flags, 1, 0, ret);
			current = current->next;
		}
	}
	return (ft_lstclear(&files, destroy_file), free(path), ret);
}


// TODO: Fix -t with single files


int	main(int argc, char **argv)
{
	t_ls_args	args;
	int			ret;
	char		*file_name;

	ret = 0;
	if (argc == 1)
		return (ls(ft_strdup("."), 0, 0, 1, 0));
	if (parse(argc, argv, &args) < 0)
		return (ft_lstclear(&args.files, free), 2);
	t_list *current = args.files;
	while (current) {
		file_name = ((t_file *)current->content)->name;
		ret = ls(ft_strdup(file_name),
			args.flags, ((ft_lstsize(args.files) > 1)
			|| (args.flags & RECURSIVE)), current == args.files, ret);
		current = current->next;
	}
	return (ft_lstclear(&args.files, free), ret);
}
