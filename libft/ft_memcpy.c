/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:16:42 by ayassin           #+#    #+#             */
/*   Updated: 2021/12/26 18:24:27 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* copy "n" bytes from "src" to "dst" and return "dst"
**NOT PROTECTED VS NULL INPUT**/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	pos;

	pos = 0;
	if (dst != 0 || src != 0)
	{
		while (pos < n)
		{
			((unsigned char *)dst)[pos] = ((unsigned char *)src)[pos];
			pos++;
		}
	}
	return (dst);
}
