/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:12:58 by ayassin           #+#    #+#             */
/*   Updated: 2021/12/26 18:17:11 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns String "s" after the first instance of char "c" (inclusive) 
within the first "n" chars. Returns NULL otherwize
**NOT PROTECTED VS NULL INPUT**/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	pos;

	pos = 0;
	c = (unsigned char) c;
	while (pos < n)
	{
		if (((unsigned char *)s)[pos] == c)
			return (&((unsigned char *)s)[pos]);
		pos++;
	}
	return (0);
}
