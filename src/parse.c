/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:26:43 by bammar            #+#    #+#             */
/*   Updated: 2024/06/25 20:31:31 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	parse(int argc, char **argv, t_ls_args *args)
{
	int		i;
	int		flags;
	t_dlist	*file_node;

	i = 0;
	flags = 0;
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
			file_node = ft_dlstnew(argv[i]);
			if (!file_node)
				return (ft_putendl_fd("ft_ls: No memory", 2), -1);
			ft_dqadd_last(args->files, file_node);
		}
	}
	args->flags = flags;
	return (0);
}
