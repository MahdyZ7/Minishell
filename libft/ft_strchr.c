/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:33:09 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/02 18:09:15 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the first occurenc of char "c" in string "s" (null inclusive).
Returns NULL otherwise
**NOT PROTECTED VS NULL INPUT**/
char	*ft_strchr(const char *s, int c)
{
	int	pos;

	pos = 0;
	c = (unsigned char) c;
	while (s[pos])
	{
		if (s[pos] == c)
			return ((char *)&(s[pos]));
		pos++;
	}
	if (s[pos] == c)
		return ((char *)&(s[pos]));
	return (0);
}
