/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:51:11 by ayassin           #+#    #+#             */
/*   Updated: 2021/12/26 20:16:44 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Copy from string "src" to overwrite "dst" till "dstsize" - 1 and terminate
Return the length of "src" or 0 for "dstsize = 0"*/
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	pos;
	size_t	len;

	pos = 0;
	while (src[pos])
		pos++;
	if (dstsize == 0)
		return (pos);
	len = pos;
	pos = 0;
	while (pos < (dstsize - 1) && src[pos])
	{
		dst[pos] = src[pos];
		pos++;
	}
	dst[pos] = 0;
	return (len);
}
