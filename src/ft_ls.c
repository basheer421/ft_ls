/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:48:57 by bammar            #+#    #+#             */
/*   Updated: 2024/06/30 20:00:25 by bammar           ###   ########.fr       */
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
		if (lstat(join_path(path, file->name), &file->stats) < 0)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&files, ft_lstnew(file));
		entry = readdir(dir);
	}
	closedir(dir);
	ret = files->next;
	ft_lstdelone(files, destroy_file);
	return (ret);
}

char	get_file_type(struct stat *stats)
{
	if (S_ISREG(stats->st_mode))
		return ('-');
	if (S_ISDIR(stats->st_mode))
		return ('d');
	if (S_ISCHR(stats->st_mode))
		return ('c');
	if (S_ISBLK(stats->st_mode))
		return ('b');
	if (S_ISFIFO(stats->st_mode))
		return ('p');
	if (S_ISLNK(stats->st_mode))
		return ('l');
	if (S_ISSOCK(stats->st_mode))
		return ('s');
	return ('-');

}

char	get_mode(int mode, char letter)
{
	if (mode)
		return (letter);
	return ('-');
}

static void	print_origin_if_link(t_file *file, int is_link)
{
	char		origin[PATH_MAX];
	ssize_t		len;

	if (is_link)
	{
		len = readlink(file->name, origin, PATH_MAX);
		if (len < 0)
			exit(EXIT_FAILURE);
		origin[len] = '\0';
		ft_printf(" -> %s", origin);
	}
}

void	print_long(t_file *file)
{
	struct stat	*stats;
	char		*time_str;
	char		file_type;

	stats = &file->stats;
	time_str = ft_strtrim(ctime(&stats->st_mtime) + 4, "\n");
	if (!time_str)
		exit(EXIT_FAILURE);
	file_type = get_file_type(stats);
	ft_printf("%c%c%c%c%c%c%c%c%c%c %d %s %s  %u %s %s",
		file_type,
		get_mode((stats->st_mode & S_IRUSR), 'r'),
		get_mode((stats->st_mode & S_IWUSR), 'w'),
		get_mode((stats->st_mode & S_IXUSR), 'x'),
		get_mode((stats->st_mode & S_IRGRP), 'r'),
		get_mode((stats->st_mode & S_IWGRP), 'w'),
		get_mode((stats->st_mode & S_IXGRP), 'x'),
		get_mode((stats->st_mode & S_IROTH), 'r'),
		get_mode((stats->st_mode & S_IWOTH), 'w'),
		get_mode((stats->st_mode & S_IXOTH), 'x'),
		stats->st_nlink,
		getpwuid(stats->st_uid)->pw_name, getgrgid(stats->st_gid)->gr_name,
		(unsigned int)stats->st_size, time_str, file->name);
	print_origin_if_link(file, file_type == 'l');
}

void	print_file(t_file *file, int flags, int is_last)
{

	if (file->name[0] != '.' || (flags & ALL))
	{
		if (flags & LONG)
			print_long(file);
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

int	ls(char *path, int flags, int print_dir_name, int origin, int ret)
{
	t_list	*files;
	t_list	*current;
	t_file	*file;

	files = get_files(path);
	if (!files || ret)
		ret = 1;
	sort_files(&files, flags);
	if (!origin && print_dir_name)
		ft_printf("\n");
	if (print_dir_name && path[0])
		ft_printf("%s:\n", path);
	if (flags & LONG)
		ft_printf("total %u\n", get_total_blocks(files));
	current = files;
	while (current)
	{
		file = current->content;
		print_file(file, flags, !current->next);
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
		return (ft_dqdel(args.files, 0), ls(ft_strdup("."), 0, 0, 1, 0));
	if (parse(argc, argv, &args) < 0)
		return (ft_dqdel(args.files, free), 2);
	t_dlist *current = args.files->head;
	while (current) {
		ret = ls(ft_strdup(current->content), args.flags, (ft_lstsize((t_list *)args.files->head) > 1)
			|| (args.flags & RECURSIVE), current == args.files->head, ret);
		current = current->next;
	}
	return (ft_dqdel(args.files, free), ret);
}
