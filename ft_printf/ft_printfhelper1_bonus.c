/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfhelper1_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:53:18 by ayassin           #+#    #+#             */
/*   Updated: 2022/01/30 15:41:17 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* This file is to print chars and strings */

/* Prints char "c" with bool "dash" and int "width" flag settings
Returns number of printed chars*/
int	ft_printfchar_b(int c, int dash, int width)
{
	int	len;

	len = 0;
	c = (char) c;
	if (dash)
	{
		write(1, &c, 1);
		while (++len < width)
			write(1, " ", 1);
		return (len);
	}
	while (++len < width)
		write(1, " ", 1);
	write(1, &c, 1);
	return (len);
}

/* Prints string "str" with flag settings 
(only width[0], precision[1],  -[2], .[5])
Returns number of printed chars*/
int	ft_printfstr_b(char *str, int *flags)
{
	int	i;
	int	slen;
	int	spclen;
	int	nullflag;

	i = 0;
	spclen = 0;
	nullflag = 0;
	if (!str)
		str = ft_strdup("(null)") + (0 * ++nullflag);
	slen = (int) ft_strlen(str);
	if (slen > flags[1] && flags[5])
		slen = flags[1];
	if (slen < flags[0])
		spclen = flags[0] - slen;
	if (flags[2])
		write(1, str, slen);
	while (i++ < spclen)
		write(1, " ", 1);
	if (!flags[2])
		write(1, str, slen);
	if (nullflag)
		free(str);
	return (slen + spclen);
}
