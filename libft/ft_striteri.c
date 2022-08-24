/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:34:30 by ayassin           #+#    #+#             */
/*   Updated: 2021/12/26 20:19:27 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Apply function "f" to each char of string "s"*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	pos;

	pos = 0;
	if (s)
	{
		while (s[pos])
		{
			f(pos, &(s[pos]));
			pos++;
		}
	}
}
