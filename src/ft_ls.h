/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:45:54 by bammar            #+#    #+#             */
/*   Updated: 2024/07/01 21:56:41 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <stdio.h>
# include <dirent.h>
# include <limits.h>
# include <string.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

// #ifndef DT_DIR
// # define DT_DIR 4
// #endif

typedef enum s_flags
{
	ALL = 1,
	LONG = 2,
	RECURSIVE = 4,
	REVERSE = 8,
	TIME = 16
}	t_flag;

typedef struct s_ls_args
{
	t_list		*files;
	int			flags;
}	t_ls_args;

typedef struct s_file
{
	char		*name;
	struct stat	stats;
	char		*full_path;
}	t_file;

int		parse_flags(char *arg);
int		parse(int argc, char **argv, t_ls_args *args);
void    destroy_file(void *file);
int 	has_recursion(char *name, int flags);
char    *join_path(char *path, char *name);
void	sort_files(t_list **files, int flags);
void    sort_args(t_ls_args *args);
char	get_file_type(struct stat *stats);
void	print_long(t_file *file, int max_len);
int		get_max_len(t_list *files);
int 	get_len(long n);

#endif
