/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:45:54 by bammar            #+#    #+#             */
/*   Updated: 2024/06/25 05:19:52 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <stdio.h>
# include <dirent.h>
# include <limits.h>

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

typedef enum s_flags
{
	ALL = 1,
	LONG = 2,
	RECURSIVE = 4,
	REVERSE = 8,
	TIME = 16
}	t_flags;

#endif
