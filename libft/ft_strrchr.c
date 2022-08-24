/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:59:15 by ayassin           #+#    #+#             */
/*   Updated: 2021/12/26 20:33:07 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return the last occurnce of char "c" in string "s" till the end of "s"*/
char	*ft_strrchr(const char *s, int c)
{
	int		pos;

	pos = 0;
	c = (unsigned char) c;
	while (s[pos])
		++pos;
	while (pos >= 0)
	{
		if (s[pos] == c)
			return ((char *)&(s[pos]));
		--pos;
	}
	return (0);
}
