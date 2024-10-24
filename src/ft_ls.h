/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 03:45:54 by bammar            #+#    #+#             */
/*   Updated: 2024/10/22 23:54:06 by bammar           ###   ########.fr       */
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

typedef struct s_settings
{
	int		print_dir;
	int		origin;
	int		ret;
}	t_settings;

# ifdef __APPLE__
#  define BLOCK_SIZE 1024
# else
#  define BLOCK_SIZE 512
# endif

int				parse_flags(char *arg);
int				parse(int argc, char **argv, t_ls_args *args);
void			destroy_file(void *file);
int				has_recursion(t_file *file, int flags);
char			*join_path(char *path, char *name);
void			sort_files(t_list **files, int flags);
char			get_file_type(struct stat *stats);
void			print_long(t_file *file, int *max_len);
int				get_max_len(t_list *files);
int				get_max_len_links(t_list *files);
int				get_len(long n);
t_list			*get_files(char *path, int flags);
void			print_file(t_file *file, int flags, int is_last, int *max_len);
unsigned int	get_total_blocks(t_list *files, int flags);
int				handle_single_file(t_list *files,
					int flags, int *max_len, char *path);
int				ls(char *path, int flags, t_settings s);
void			rev(t_list **files);

#endif
