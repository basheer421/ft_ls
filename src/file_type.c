/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 03:18:38 by bammar            #+#    #+#             */
/*   Updated: 2024/06/30 03:24:24 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    destroy_file(void *file)
{
	if (!file)
		return ;
	free(((t_file *)file)->name);
	free(file);
}

int has_recursion(char *name, int flags)
{
	if (name[0] == '.')
	{
        if (!(flags & ALL))
            return (0);
		if (name[1] == '\0')
			return (0);
		if (name[1] == '.' && name[2] == '\0')
			return (0);
	}
	return (1);
}

char    *join_path(char *path, char *name)
{
	char	*ret;
	size_t	path_len;
	size_t	name_len;

	path_len = ft_strlen(path);
	name_len = ft_strlen(name);
	ret = ft_malloc(path_len + name_len + 2);
	if (!ret)
		exit(EXIT_FAILURE);
	ft_strlcpy(ret, path, path_len + 1);
	ft_strlcpy(ret + path_len, "/", 2);
	ft_strlcpy(ret + path_len + 1, name, name_len + 1);
	return (ret);
}
