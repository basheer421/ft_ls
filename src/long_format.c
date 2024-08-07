/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:34:13 by bammar            #+#    #+#             */
/*   Updated: 2024/07/02 03:06:14 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	get_mode(int mode, char letter)
{
	if (mode)
		return (letter);
	return ('-');
}

static void	print_origin_if_link(t_file *file, int is_link)
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

static void	print_second_part(t_file *file, int max_len)
{
	struct stat			*stats;
	char				byte_str_buf[LTOA_BUF_SIZE];
	char				*time_str;
	int					len;

	stats = &file->stats;
	time_str = ctime(&stats->st_mtime) + 4;
	time_str[12] = 0;
	len = get_len(stats->st_size);
	if (len > max_len)
		max_len = len;
	while (len++ < max_len)
		ft_printf(" ");
	ft_ltoa(stats->st_size, byte_str_buf);
	ft_printf(" %s", byte_str_buf);
	ft_printf(" %s %s", time_str, file->name);
}

static void	print_first_part(t_file *file, int max_len)
{
	struct stat			*stats;
	char				byte_str_buf[LTOA_BUF_SIZE];
	int					len;

	stats = &file->stats;
	len = get_len(stats->st_nlink);
	if (len > max_len)
		max_len = len;
	while (len++ < max_len)
		ft_printf(" ");
	ft_ltoa(stats->st_nlink, byte_str_buf);
	ft_printf("%s", byte_str_buf);
	ft_printf(" %s  %s ", getpwuid(stats->st_uid)->pw_name,
		getgrgid(stats->st_gid)->gr_name);
}

void	print_long(t_file *file, int *max_len)
{
	struct stat	*stats;
	char		file_type;

	stats = &file->stats;
	file_type = get_file_type(stats);
	ft_printf("%c%c%c%c%c%c%c%c%c%c  ",
		file_type,
		get_mode((stats->st_mode & S_IRUSR), 'r'),
		get_mode((stats->st_mode & S_IWUSR), 'w'),
		get_mode((stats->st_mode & S_IXUSR), 'x'),
		get_mode((stats->st_mode & S_IRGRP), 'r'),
		get_mode((stats->st_mode & S_IWGRP), 'w'),
		get_mode((stats->st_mode & S_IXGRP), 'x'),
		get_mode((stats->st_mode & S_IROTH), 'r'),
		get_mode((stats->st_mode & S_IWOTH), 'w'),
		get_mode((stats->st_mode & S_IXOTH), 'x'));
	print_first_part(file, max_len[1]);
	print_second_part(file, max_len[0]);
	print_origin_if_link(file, file_type == 'l');
}
