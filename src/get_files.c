/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 01:38:18 by bammar            #+#    #+#             */
/*   Updated: 2024/10/23 00:14:20 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*try_single_file(char *path)
{
	t_file	*file;

	file = ft_malloc(sizeof(t_file));
	file->name = ft_strdup(path);
	if (!file->name)
		exit(EXIT_FAILURE);
	lstat(path, &file->stats);
	file->full_path = ft_strdup(path);
	if (!file->full_path)
		exit(EXIT_FAILURE);
	if (S_ISDIR(file->stats.st_mode))
		return (destroy_file(file), perror("ft_ls"), NULL);
	return (ft_lstnew(file));
}

static t_file	*get_file(char *path, char *name)
{
	t_file	*file;

	file = ft_malloc(sizeof(t_file));
	file->name = ft_strdup(name);
	if (!file->name)
		exit(EXIT_FAILURE);
	file->full_path = join_path(path, file->name);
	lstat(file->full_path, &file->stats);
	return (file);
}

t_list	*get_files(char *path, int flags)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*files;
	t_list			*ret;

	if (!*path)
		return (NULL);
	dir = opendir(path);
	if (!dir)
		return (try_single_file(path));
	files = ft_lstnew(NULL);
	entry = readdir(dir);
	while (entry)
	{
		if ((flags & ALL) || entry->d_name[0] != '.')
			ft_lstadd_back(&files, ft_lstnew(get_file(path, entry->d_name)));
		entry = readdir(dir);
	}
	closedir(dir);
	ret = files->next;
	ft_lstdelone(files, destroy_file);
	return (ret);
}
