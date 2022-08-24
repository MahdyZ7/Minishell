/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:17:21 by ayassin           #+#    #+#             */
/*   Updated: 2021/12/26 14:24:59 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Same as ft_memcpy (n bytes from src to dst) but avoids collisions
**NOT PROTECTED VS NULL INPUT*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	pos;

	if (dst != 0 || src != 0)
	{
		if (dst > src)
		{
			pos = len;
			while (pos-- > 0)
			{
				((unsigned char *)dst)[pos] = ((unsigned char *)src)[pos];
			}
		}
		else
		{
			pos = 0;
			while (pos < len)
			{
				((unsigned char *)dst)[pos] = ((unsigned char *)src)[pos];
				pos++;
			}
		}
	}
	return (dst);
}
