/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:48:57 by bammar            #+#    #+#             */
/*   Updated: 2024/06/25 20:32:02 by bammar           ###   ########.fr       */
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

	if (!init_args(&args))
		return (ft_putendl_fd("ft_ls: No memory", 2), 1);
	if (argc == 1)
		return (ls(".", 0));
	if (parse(argc, argv, &args) < 0)
		return (ft_dqdel(args.files, 0), 1);
	t_dlist *current = args.files->head;
	while (current) {
		ft_printf("{%s}\n", current->content);
		current = current->next;
	}
	return (ft_dqdel(args.files, 0), 0);
}
