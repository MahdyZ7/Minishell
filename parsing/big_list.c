/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 09:49:19 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:50:49 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_add_front(t_new **cmd, t_list *lst)
{
	t_new	*temp;

	while (lst)
	{
		temp = malloc(sizeof(t_new));
		ft_lstadd_back(&g_m, ft_lstnew((void *)(temp)));
		temp->token = (char *)lst->content;
		temp->es = NULL;
		temp->lst = NULL;
		temp->d_flag = 0;
		temp->flag = 4;
		temp->s_flag = (*cmd)->s_flag;
		(*cmd)->prev->next = temp;
		temp->prev = (*cmd)->prev;
		temp->next = (*cmd);
		(*cmd)->prev = temp;
		lst = lst->next;
	}
}

void	lst_big_new(t_new **cmd, t_list *lst)
{
	t_new	*temp;

	while (lst)
	{
		temp = malloc(sizeof(t_new));
		ft_lstadd_back(&g_m, ft_lstnew((void *)(temp)));
		temp->token = (char *)lst->content;
		temp->es = NULL;
		temp->lst = NULL;
		temp->d_flag = 0;
		temp->flag = 4;
		temp->s_flag = (*cmd)->s_flag;
		if ((*cmd)->prev == NULL)
			temp->prev = NULL;
		else
		{
			temp->s_flag = (*cmd)->s_flag;
			temp->prev = (*cmd)->prev;
			(*cmd)->prev->next = temp;
		}
		temp->next = (*cmd);
		(*cmd)->prev = temp;
		lst = lst->next;
	}
}
