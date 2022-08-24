/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:13:57 by ayassin           #+#    #+#             */
/*   Updated: 2021/12/26 18:21:35 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return a new list that f(lst -> content) as conent.
Returns NULL & "del" the content of new list if the "lst" has NULL content
**malloc DANGER**/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nwlst;

	if (!lst)
		return (NULL);
	nwlst = NULL;
	while (lst)
	{
		if ((lst->content) == NULL)
		{
			ft_lstclear(&nwlst, del);
			return (NULL);
		}
		ft_lstadd_back(&nwlst, ft_lstnew(f(lst->content)));
		lst = lst->next;
	}
	return (nwlst);
}
