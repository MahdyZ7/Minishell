/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:34:02 by ayassin           #+#    #+#             */
/*   Updated: 2021/12/26 10:58:03 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* add "wen" node to the end of the "lst"*/
void	ft_lstadd_back(t_list **lst, t_list *wen)
{
	t_list	*temp;

	if (lst)
	{
		temp = *lst;
		if (!(*lst))
		{
			*lst = wen;
			return ;
		}
		while ((*lst)->next != 0)
			*lst = (*lst)->next;
		(*lst)->next = wen;
		*lst = temp;
	}
}
