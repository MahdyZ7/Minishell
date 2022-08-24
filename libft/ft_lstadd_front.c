/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:41:42 by ayassin           #+#    #+#             */
/*   Updated: 2021/12/26 10:57:59 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Add node "wen" to the fron of "lst"*/
void	ft_lstadd_front(t_list **lst, t_list *wen)
{
	wen -> next = *lst;
	*lst = wen;
}
