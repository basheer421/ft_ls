/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:54:08 by bammar            #+#    #+#             */
/*   Updated: 2024/07/02 03:06:43 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*reverse(char *str)
{
	int		len;
	int		i;
	char	temp;
	char	*s;

	s = str;
	len = 0;
	while (s[len] != 0)
		len++;
	i = 0;
	while (i < len / 2)
	{
		temp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = temp;
		i++;
	}
	return (s);
}

static int	get_len(unsigned long long n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_ltoa(unsigned long long n, char *buf)
{
	int					i;
	int					len;

	len = get_len(n);
	ft_bzero(buf, 20);
	i = 0;
	while (i < len)
	{
		buf[i++] = '0' + (n % 10);
		n = n / 10;
	}
	buf[i] = 0;
	buf = reverse(buf);
	return (buf);
}
