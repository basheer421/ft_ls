/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:56:33 by bammar            #+#    #+#             */
/*   Updated: 2024/06/25 05:09:21 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_hexa(unsigned long long n, int small)
{
	unsigned long long	x;
	char				final[100];
	int					rem;
	int					i;
	int					j;

	x = n;
	i = 0;
	if (n == 0)
		return (pf_putchar_fd('0', 1));
	while (x != 0)
	{
		rem = x % 16;
		if (rem < 10)
			final[i++] = rem + '0';
		else
			final[i++] = ('A' + rem - 10) + (small * ('a' - 'A'));
		x = x / 16;
	}
	final[i] = 0;
	j = (int)pf_strlen(final);
	while (j >= 1)
		pf_putchar_fd(final[--j], 1);
	return ((int)pf_strlen(final));
}

static int	print_pointer(unsigned long long p)
{
	int	count;

	count = pf_putstr_fd("0x", 1);
	return (count + print_hexa(p, 1));
}

static int	pf_putunbr_fd(unsigned int n, int fd)
{
	int		count;
	char	c;

	c = '0';
	count = 0;
	if (n < 10)
	{
		c += n;
		count += pf_putchar_fd(c, 1);
	}
	else
	{
		count += pf_putunbr_fd(n / 10, fd);
		count += pf_putunbr_fd(n % 10, fd);
	}
	return (count);
}

static int	print_case(const char *format, va_list ap, int i)
{
	if (format[i + 1] == '%')
		return (pf_putchar_fd('%', 1));
	else if (format[i + 1] == 's')
		return (pf_putstr_fd((char *)va_arg(ap, char *), 1));
	else if (format[i + 1] == 'c')
		return (pf_putchar_fd(((char)va_arg(ap, int)), 1));
	else if (format[i + 1] == 'd' || format[i + 1] == 'i')
		return (pf_putnbr_fd((int)va_arg(ap, int), 1));
	else if (format[i + 1] == 'u')
		return (pf_putunbr_fd(va_arg(ap, int), 1));
	else if (format[i + 1] == 'p')
		return (print_pointer(va_arg(ap, unsigned long long)));
	else if (format[i + 1] == 'x')
		return (print_hexa(va_arg(ap, unsigned int), 1));
	else if (format[i + 1] == 'X')
		return (print_hexa(va_arg(ap, unsigned int), 0));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		counter;

	va_start(ap, format);
	i = 0;
	counter = 0;
	while (format[i] != 0)
	{
		if (format[i] == '%')
			counter += print_case(format, ap, i);
		else
			counter += pf_putchar_fd(format[i], 1);
		if (format[i] == '%')
			i += 2;
		else
			i++;
	}
	va_end(ap);
	return (counter);
}
