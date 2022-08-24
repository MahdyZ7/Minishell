/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:56:20 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/28 06:50:51 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_switch(va_list args, char ptr_type);

/*Mimmics printf with no flags*/
int	ft_printf(const char *str, ...)
{
	int		pos;
	int		len;
	va_list	printf_args;

	pos = 0;
	len = 0;
	va_start(printf_args, str);
	while (str[pos])
	{
		if (str[pos] == '%')
		{
			++pos;
			len += ft_printf_switch(printf_args, str[pos]);
		}
		else
		{
			write(1, &str[pos], 1);
			++len;
		}
		++pos;
	}
	return (len);
}

static int	ft_printf_switch(va_list args, char ptr_type)
{
	int	len;

	len = 0;
	if (ptr_type == '%')
		ft_putchar_fd('%' + (0 * ++len), 1);
	else if (ptr_type == 'c')
		ft_putchar_fd(va_arg(args, int) + (0 * ++len), 1);
	else if (ptr_type == 's')
		len += ft_printfstr(va_arg(args, char *));
	else if (ptr_type == 'p')
		len += ft_printfptr(va_arg(args, long long int));
	else if (ptr_type == 'x' || ptr_type == 'X' || ptr_type == 'u')
		len += ft_printfunsgned(va_arg(args, unsigned int),
				16 - 6 * (ptr_type == 'u'), ptr_type == 'X');
	else if (ptr_type == 'i' || ptr_type == 'd')
		len += ft_printfint(va_arg(args, int));
	return (len);
}
