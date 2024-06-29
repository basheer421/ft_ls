/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:32:56 by bammar            #+#    #+#             */
/*   Updated: 2024/06/25 05:09:19 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	pf_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	pf_putchar_fd(int c, int fd)
{
	char	x;

	x = c;
	write(fd, &x, 1);
	return (1);
}

int	pf_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != 0)
			write(fd, &s[i++], 1);
	}
	else
	{
		write(fd, "(null)", 6);
		return (6);
	}
	return (i);
}

int	pf_putnbr_fd(int n, int fd)
{
	char	c;
	int		count;

	c = '0';
	count = 0;
	if (n == -2147483648)
	{
		count += pf_putstr_fd("-214", 1);
		count += pf_putnbr_fd(7483648, fd);
	}
	else if (n < 0)
	{
		count += pf_putstr_fd("-", 1);
		count += pf_putnbr_fd(n * -1, fd);
	}
	else if (n < 10)
		count += pf_putchar_fd(c + n, 1);
	else
	{
		count += pf_putnbr_fd(n / 10, fd);
		count += pf_putnbr_fd(n % 10, fd);
	}
	return (count);
}
