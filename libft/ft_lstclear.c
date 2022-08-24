/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:08:19 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/26 13:51:38 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Uses the "del" function on the contents of the "lst" and frees all nodes*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*tempnext;

	if (lst)
	{
		temp = *lst;
		while (temp != 0)
		{
			tempnext = temp -> next;
			if (temp->content)
			{
				del(temp -> content);
				temp->content = NULL;
			}
			free(temp);
			temp = tempnext;
		}
		*lst = 0;
	}
}
