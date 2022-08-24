/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:35:16 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/19 20:43:36 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Join string "s2" to "s1" in a new string "temp" and returns it
**malloc DANGER**/
char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned long	len;
	unsigned long	pos;
	unsigned long	pos1;
	char			*temp;

	pos = 0;
	pos1 = 0;
	len = 1;
	if (s1)
		len += (unsigned long)ft_strlen(s1);
	if (s2)
		len += (unsigned long)ft_strlen(s2);
	temp = (char *)malloc((len) * sizeof(char));
	if (!temp)
		return (0);
	while (pos < len && s1 && s1[pos])
	{
		temp[pos] = s1[pos];
		++pos;
	}
	while (pos < len && s2[pos1])
		temp[pos++] = s2[pos1++];
	temp[pos] = 0;
	return (temp);
}
