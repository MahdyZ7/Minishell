/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:52:57 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/20 17:54:35 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return int length of string "s1"
**PROTECTED VS NULL INPUT**/
int	ft_strlen(const char *s)
{
	int	len;

	if (s == NULL)
		return (0);
	len = -1;
	while (s[++len])
		;
	return (len);
}
