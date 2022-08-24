/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:11:32 by ayassin           #+#    #+#             */
/*   Updated: 2021/12/26 14:31:10 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* write char "c" in output in file discriptor "fd" (make fd =1)*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
