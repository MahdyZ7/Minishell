/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 08:31:01 by ayassin           #+#    #+#             */
/*   Updated: 2022/01/30 15:00:44 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_printf_switch(va_list ptr, int *flags, char prt_typ);
static int	flagset(const char *str, int *flags);
static int	indexof(char c, char *t);

/* Prints the string "str" with variable arguments accessed by %[type] in str.
Returns the length of the printed statment*/
int	ft_printf(const char *str, ...)
{
	int		pos;
	int		len;
	int		flags[8];
	va_list	printf_args;

	pos = 0;
	len = 0;
	va_start(printf_args, str);
	while (str[pos])
	{
		if (str[pos] == '%')
		{
			pos++;
			pos += flagset(&(str[pos]), flags);
			len += ft_printf_switch(printf_args, flags, str[pos]);
			++pos;
		}
		else if (str[pos])
		{
			write(1, &(str[pos++]), 1);
			++len;
		}
	}
	va_end(printf_args);
	return (len);
}

/*Calls the printf helper functions based on the char "prtr_typ"
 (c ,s , p, x, X, u, i, d, %), the arguments ("args"), and flags ("flags")
 Returns the length of the printed statemnet*/
static int	ft_printf_switch(va_list args, int *flags, char prt_typ)
{
	int	len;

	len = 0;
	if (prt_typ == 'c')
		len += ft_printfchar_b(va_arg(args, int), flags[2], flags[0]);
	else if (prt_typ == 's')
		len += ft_printfstr_b(va_arg(args, char *), flags);
	else if (prt_typ == 'p')
		len += ft_printfptr_b(va_arg(args, size_t), flags[2], flags[0]);
	else if (prt_typ == 'x' || prt_typ == 'X')
		len += ft_printfunsgned_b(va_arg(args, unsigned int), flags, 16,
				(prt_typ - 'x'));
	else if (prt_typ == 'u')
		len += ft_printfunsgned_b(va_arg(args, unsigned int), flags, 10, 0);
	else if (prt_typ == 'i' || prt_typ == 'd')
		len += ft_printfint_b(va_arg(args, int), flags);
	else if (prt_typ == '%')
		len += ft_printfchar_b('%', 0, 0);
	return (len);
}

/* Sets the 8 flags in str to the array flags[width precision - + _ . # 0] 
Returns the length of the flags for skipping */
static int	flagset(const char *str, int *flags)
{
	int		pos;
	char	*validflags;

	pos = -1;
	validflags = "-+ -#0";
	while (++pos < 8)
		flags[pos] = 0;
	pos = 0;
	while (str[pos] && indexof(str[pos], validflags) != -1)
	{
		flags[indexof(str[pos], validflags) + 2]++;
		pos++;
	}
	while (str[pos] && ft_isdigit(str[pos]))
		flags[0] = flags[0] * 10 + (str[pos++] - 48);
	if (str[pos] == '.')
	{
		++flags[5];
		pos++;
	}
	while (str[pos] && ft_isdigit(str[pos]))
		flags[1] = flags[1] * 10 + (str[pos++] - 48);
	return (pos);
}

/* Returns the first index of char "c" in string "t", -1 otherwise*/
static int	indexof(char c, char *t)
{
	int	pos;

	pos = 0;
	while (t[pos])
	{
		if (t[pos] == c)
			return (pos);
		pos++;
	}
	return (-1);
}
