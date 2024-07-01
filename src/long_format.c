/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:34:13 by bammar            #+#    #+#             */
/*   Updated: 2024/07/01 21:58:19 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char get_mode(int mode, char letter)
{
	if (mode)
		return (letter);
	return ('-');
}

static void print_origin_if_link(t_file *file, int is_link)
{
	char		origin[PATH_MAX];
	ssize_t		len;

	if (is_link)
	{
		len = readlink(file->full_path, origin, PATH_MAX);
		if (len < 0)
			ft_printf(" -> ");
		else
		{
			origin[len] = '\0';
			ft_printf(" -> %s", origin);
		}
	}
}

static void print_second_part(t_file *file, int max_len)
{
	struct stat	*stats;
	char	byte_str_buf[LTOA_BUF_SIZE];
	char	*time_str;
    int        len;

	stats = &file->stats;
    time_str = ft_strtrim(ctime(&stats->st_mtime) + 4, "\n");
	if (!time_str)
		exit(8);
    len = get_len(stats->st_size);
    if (len > max_len)
        max_len = len;
    while (len++ < max_len)
        ft_printf(" ");
    ft_ltoa(stats->st_size, byte_str_buf);
	ft_printf("%s", byte_str_buf);    
	ft_printf(" %s %s", time_str, file->name);
    free(time_str);
}

void	print_long(t_file *file, int max_len)
{
	struct stat	*stats;
	char		file_type;

	stats = &file->stats;
	file_type = get_file_type(stats);
	ft_printf("%c%c%c%c%c%c%c%c%c%c %d %s %s ",
		file_type,
		get_mode((stats->st_mode & S_IRUSR), 'r'),
		get_mode((stats->st_mode & S_IWUSR), 'w'),
		get_mode((stats->st_mode & S_IXUSR), 'x'),
		get_mode((stats->st_mode & S_IRGRP), 'r'),
		get_mode((stats->st_mode & S_IWGRP), 'w'),
		get_mode((stats->st_mode & S_IXGRP), 'x'),
		get_mode((stats->st_mode & S_IROTH), 'r'),
		get_mode((stats->st_mode & S_IWOTH), 'w'),
		get_mode((stats->st_mode & S_IXOTH), 'x'),
		stats->st_nlink,
		getpwuid(stats->st_uid)->pw_name, getgrgid(stats->st_gid)->gr_name);
	print_second_part(file, max_len);
	print_origin_if_link(file, file_type == 'l');
}
