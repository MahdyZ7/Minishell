/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:08:08 by ayassin           #+#    #+#             */
/*   Updated: 2021/12/26 12:03:21 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* returns allocated memory for "count" objects each with "size" bytes 
**malloc DANGER* */
void	*ft_calloc(size_t count, size_t size)
{
	void	*x;
	size_t	i;
	size_t	j;
	size_t	pos;

	pos = 0;
	i = 0;
	x = (void *)malloc(count * size * sizeof(unsigned char));
	if (!x)
		return (0);
	while (i < count)
	{
		j = 0;
		while (j < size)
		{
			((unsigned char *)x)[pos] = 0;
			pos++;
			j++;
		}
		i++;
	}
	return (x);
}
