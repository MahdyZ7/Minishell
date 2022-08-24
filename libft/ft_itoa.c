/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:10:47 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/01 15:21:10 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* sets the first char of the string "temp" to 0 or -,
if "num" is zero or negative respectivly*/
static void	zerneg(long *num, char *temp)
{
	if (*num < 0)
	{
		temp[0] = '-';
		*num *= -1;
	}
	if (*num == 0)
		temp[0] = '0';
}

/* Returns a string of integer "n"
**malloc DANGER**/
char	*ft_itoa(int n)
{
	int		len;
	long	clone;
	char	*temp;

	len = 0;
	clone = n;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	temp = (char *)malloc((len + 1) * sizeof(char));
	if (!temp)
		return (0);
	temp[len--] = 0;
	if (clone <= 0)
		zerneg(&clone, temp);
	while (clone > 0)
	{
		temp[len--] = clone % 10 + '0';
		clone /= 10;
	}
	return (temp);
}
