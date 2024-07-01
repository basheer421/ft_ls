/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:48:57 by bammar            #+#    #+#             */
/*   Updated: 2024/07/02 03:09:52 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	init_ls(char *path, int flags, t_list **files, int *max_len)
{
	*files = get_files(path);
	if (*files == NULL)
		return (free(path), 0);
	*max_len = get_max_len(*files);
	sort_files(files, flags);
	return (1);
}

void	print_headers(t_list *files, char *path,
	int flags, t_settings s)
{
	if (!s.origin && s.print_dir)
		ft_printf("\n");
	if (s.print_dir)
		ft_printf("%s:\n", path);
	if ((flags & LONG))
		ft_printf("total %u\n", get_total_blocks(files));
}

void	recursion(t_list *files, t_settings *s, char *path, int flags)
{
	t_list	*current;

	current = files;
	while (current)
	{
		if (has_recursion(current->content, flags))
			s->ret = ls(join_path(path, ((t_file *) current->content)->name), \
					flags, *s);
		current = current->next;
	}
}

int	ls(char *path, int flags, t_settings s)
{
	t_list		*files;
	t_list		*current;
	int			mlen;

	if (!init_ls(path, flags, &files, &mlen) \
		|| handle_single_file(files, flags, mlen, path))
		return (s.ret);
	print_headers(files, path, flags, s);
	current = files;
	while (current)
	{
		print_file(current->content, flags, !current->next, mlen);
		current = current->next;
	}
	if (flags & RECURSIVE)
		recursion(files, &s, path, flags);
	return (ft_lstclear(&files, destroy_file), free(path), s.ret);
}

int	main(int argc, char **argv)
{
	t_ls_args	args;
	int			ret;
	char		*file_name;
	t_list		*current;
	t_settings	s;

	ret = 0;
	s = (t_settings){0, 1, 0};
	if (argc == 1)
		return (ls(ft_strdup("."), 0, s));
	if (parse(argc, argv, &args) < 0)
		return (ft_lstclear(&args.files, free), 2);
	current = args.files;
	while (current)
	{
		file_name = ((t_file *)current->content)->name;
		s.origin = (ft_lstsize(args.files) > 1);
		s.print_dir = (ft_lstsize(args.files) > 1)
			|| (args.flags & RECURSIVE);
		s.ret = ret;
		ret = ls(ft_strdup(file_name), args.flags, s);
		current = current->next;
	}
	return (ft_lstclear(&args.files, free), ret);
}
