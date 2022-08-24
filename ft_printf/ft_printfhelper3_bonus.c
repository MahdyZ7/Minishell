/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfhelper3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:06:29 by ayassin           #+#    #+#             */
/*   Updated: 2022/01/30 11:27:05 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//This file is to print pointers, intgers and digits

static void	ft_printptrhelper( long long int p, unsigned long long int p16);
static int	numlen(int num, int *flags);
static void	ft_printfhelper3(int num, int *flags, int skipflag);

/* Prints memory address p in hex, returns the length of printed chars
flags (0:width 2:-) used for bonus*/
int	ft_printfptr_b(long long int p, int dash, int width)
{
	int						len;
	unsigned long long int	pow16;

	len = 2;
	pow16 = 1;
	while (pow16 * 16 > pow16 && p / (pow16 * 16) != 0)
	{
		len++;
		pow16 *= 16;
	}
	if (dash)
		ft_printptrhelper(p, pow16);
	while (++len < width)
		write(1, " ", 1);
	if (!dash)
		ft_printptrhelper(p, pow16);
	return (len);
}

/*helper function for ft_printfptr*/
static void	ft_printptrhelper( long long int p, unsigned long long int p16)
{
	char	*hex;

	hex = "0123456789abcdef";
	write(1, "0x", 2);
	while (p16 > 0)
	{
		write(1, &(hex[p / p16]), 1);
		p %= p16;
		p16 /= 16;
	}
}

/* prints signed int "num" in base 10 and returns the length of chars printed
flags (0:width 1:pres 2:- 3:+ 4:_ 5:. 7:0) are used for bonus*/
int	ft_printfint_b(int num, int *flags)
{
	int	len;
	int	skipflag;

	if (flags[7] && !flags[5] && !flags[2])
		flags[1] = flags[0] - ((flags[3] || flags[4] || num < 0) * 1);
	len = numlen(num, flags);
	skipflag = 0;
	if (num == 0 && !flags[1] && flags[5])
	{
		skipflag = 1;
		len = (flags[3] > 0 || flags[4] > 0) * 1;
	}
	if (flags[2])
		ft_printfhelper3(num, flags, skipflag);
	while (len++ < flags[0])
		write(1, " ", 1);
	if (!flags[2])
		ft_printfhelper3(num, flags, skipflag);
	return (len - 1);
}

static int	numlen(int num, int *flags)
{
	int		len;
	long	basepow;

	len = 1;
	basepow = 1;
	while (num / (basepow * 10) != 0)
	{
		++len;
		basepow *= 10;
	}
	if (flags[1] > len)
		len = flags[1];
	if (num < 0 || flags[3] || flags[4])
		++len;
	return (len);
}

/*Helper function to print signed intb "num" with the flags.
"skipflag" are is for %.d case when d is 0*/
static void	ft_printfhelper3(int num, int *flags, int skipflag)
{
	long	pow10;
	long	numclone;
	int		len;

	pow10 = 1;
	len = -1;
	numclone = num;
	if (num < 0)
	{
		numclone *= -1;
		write (1, "-", 1);
	}
	else if (flags[3] || flags[4])
		ft_putchar_fd(' ' + (11 * (flags[3] == 1)), 1);
	while (numclone / (pow10 * 10) != (0 * ++len))
		pow10 *= 10;
	while (++len < flags[1])
		write(1, "0", 1);
	while (pow10 > 0 && !skipflag)
	{
		ft_putchar_fd('0' + (numclone / pow10), 1);
		numclone = numclone % pow10;
		pow10 = pow10 / 10;
	}
}
