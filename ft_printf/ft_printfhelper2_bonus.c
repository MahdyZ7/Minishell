/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfhelper2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:06:25 by ayassin           #+#    #+#             */
/*   Updated: 2022/01/30 15:45:34 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// This file is to print hex( x and X) and unsigned integer

static void	ft_printfhelper2(unsigned int p, int *flags, char upper,
				unsigned int base);
static int	numlen(unsigned int num, unsigned int base, char hash, int max);

/* prints unsigned int "p", in "base" 10 or 16,
"upper" is bool for upper case hex,
flags (0:width 1:pres 2:- 5:. 6:# 7:0) are used */
int	ft_printfunsgned_b(unsigned int p, int *flags, unsigned int base, char up)
{
	int	len;

	if (p == 0)
	{
		if (!flags[1] && flags[5])
		{
			len = -1;
			while (++len < flags[0])
				write(1, " ", 1);
			return (len);
		}
		flags[6] = 0;
	}
	if (flags[7] && !flags[5] && !flags[2])
		flags[1] = flags[0] - ((flags[6] > 0) * (base == 16) * 2);
	len = numlen(p, base, flags[6] > 0, flags[1]);
	if (flags[2])
		ft_printfhelper2(p, flags, up, base);
	while (len++ < flags[0])
		write(1, " ", 1);
	if (!flags[2])
		ft_printfhelper2(p, flags, up, base);
	return (len - 1);
}

/* Returns the length of digits in intger "num" in base "base"
flags hash(#) and  max(pression) are used for bonus*/
static int	numlen(unsigned int num, unsigned int base, char hash, int max)
{
	int				len;
	unsigned long	baseorder;

	len = 1;
	baseorder = 1;
	while (num / (baseorder * base) > 0)
	{
		baseorder *= base;
		++len;
	}
	if (max > len)
		len = max;
	if (hash && base == 16)
		len += 2;
	return (len);
}

/* Prints the number "num" in base "base", upper is a bool for X
flags (1:pression 6:#) are added for bounus*/
static void	ft_printfhelper2(unsigned int num, int *flags, char upper,
			unsigned int base)
{
	char			*basechar;
	int				len;
	unsigned long	baseorder;

	len = -1;
	baseorder = 1;
	basechar = ft_strdup("0123456789abcdef0x");
	while (upper && basechar[++len])
		basechar[len] = ft_toupper(basechar[len]);
	if (flags[6] && base == 16)
		write(1, &basechar[16], 2);
	len = -1;
	while (num / (baseorder * base) != (0 * ++len))
		baseorder *= base;
	while (++len < flags[1])
		write(1, "0", 1);
	while (baseorder > 0)
	{
		write(1, &basechar[num / baseorder], 1);
		num = num % baseorder;
		baseorder = baseorder / base;
	}
	free (basechar);
}
