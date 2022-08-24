/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfhelper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 08:10:02 by ayassin           #+#    #+#             */
/*   Updated: 2022/01/30 15:27:26 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* prints string str and return its lenghth*/
int	ft_printfstr(char *str)
{
	int	len;

	len = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[len])
	{
		write(1, &str[len], 1);
		++len;
	}
	return (len);
}

/* prints poiter p in hex and return its lenghth*/
int	ft_printfptr(unsigned long long int p)
{
	int						len;
	unsigned long long int	pow16;
	char					*hex;

	len = 3;
	pow16 = 1;
	hex = "0123456789abcdef";
	while ((pow16 * 16 > pow16) && p >= (pow16 * 16))
	{
		pow16 *= 16;
		++len;
	}
	write(1, "0x", 2);
	while (pow16 > 0)
	{
		write(1, &(hex[p / pow16]), 1);
		p %= pow16;
		pow16 /= 16;
	}
	return (len);
}

/* prints unsigned num in base 10 or 16 (with upper or lower case hex)
and return its lenghth*/
int	ft_printfunsgned(unsigned int num, int base, int upper)
{
	int				len;
	unsigned long	basepow;
	char			*hex;

	len = -1;
	basepow = 1;
	hex = ft_strdup("0123456789abcdef0x");
	while (upper && hex[++len])
		hex[len] = ft_toupper(hex[len]);
	len = 1;
	while (num >= basepow * base)
		basepow *= base + (0 * ++len);
	while (basepow > 0)
	{
		write(1, &(hex[num / basepow]), 1);
		num %= basepow;
		basepow /= base;
	}
	free(hex);
	return (len);
}

/* prints int num and return its lenghth*/
int	ft_printfint(int num)
{
	int		len;
	long	pow10;
	long	clone;

	len = 1;
	pow10 = 1;
	clone = num;
	if (num < 0)
	{
		clone *= -1;
		write(1, "-", 1);
		++len;
	}
	while (clone >= pow10 * 10)
	{
		pow10 *= 10;
		++len;
	}
	while (pow10 > 0)
	{
		ft_putchar_fd(('0' + clone / pow10), 1);
		clone %= pow10;
		pow10 /= 10;
	}
	return (len);
}
