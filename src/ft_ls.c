/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:48:57 by bammar            #+#    #+#             */
/*   Updated: 2024/06/25 05:39:51 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ls(char *path, int flags)
{
	DIR				*dir;
	struct dirent	*entry;
	int				add_space;

	dir = opendir(path);
	if (!dir)
	{
		perror("ls");
		return (1);
	}
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' || flags & ALL)
			ft_printf("%s", entry->d_name);
		if (flags & LONG)
			ft_printf("\n");
		if (entry && (entry->d_name[0] != '.' || flags & ALL))
			add_space = 1;
		entry = readdir(dir);
		if (entry && add_space)
			ft_printf(" ");
	}
	closedir(dir);
	return (0);
}

int	main(int argc, char **argv)
{
	char	path[PATH_MAX + 1];

	if (argc == 1)
		return (ls(".", 0));
	if (ft_strlen(argv[1]) > PATH_MAX)
	{
		perror("ft_ls");
		return (1);
	}
	ft_strlcpy(path, argv[1], PATH_MAX); // should be handled in a loop for multiple arguments
	return (ls(path, ALL | LONG));
}
