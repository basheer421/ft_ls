/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:16:28 by bammar            #+#    #+#             */
/*   Updated: 2024/06/30 04:08:57 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_flag	get_flag(char c)
{
	if (c == 'a')
		return (ALL);
	else if (c == 'l')
		return (LONG);
	else if (c == 'R')
		return (RECURSIVE);
	else if (c == 'r')
		return (REVERSE);
	else if (c == 't')
		return (TIME);
	return (0);
}

int	parse_flags(char *arg)
{
	int	i;
	int	flags;
	int	flag;

	i = -1;
	flags = 0;
	while (arg[++i])
	{
		flag = get_flag(arg[i]);
		if (!flag)
			return (-1);
		flags |= flag;
	}
	return (flags);
}
