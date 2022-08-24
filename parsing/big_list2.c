/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:27:01 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:51:25 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_add(t_new **cmd, t_list *lst)
{
	if ((*cmd)->prev == NULL)
		lst_big_new(cmd, lst);
	else
		lst_add_front(cmd, lst);
}

void	lst_skip_node2(t_new *cmd)
{
	if (cmd->prev)
		cmd->prev->next = cmd->next;
	if (cmd->next)
		cmd->next->prev = cmd->prev;
}

void	big_list_help(t_new **cmd)
{
	char	*str;
	t_list	*tmp;

	tmp = (*cmd)->lst;
	if ((*cmd)->flag == 3)
	{
		lst_add(cmd, tmp);
		lst_skip_node2(*cmd);
	}
	if ((*cmd)->flag == 1)
	{
		str = ft_strdup((*cmd)->es);
		tmp = ft_lstnew((void *)(str));
		ft_lstadd_back(&g_m, tmp);
		(*cmd)->token = str;
	}
}

void	make_big_list(t_new **cmd)
{
	t_new	*temp;

	temp = (*cmd);
	while ((*cmd) != NULL)
	{
		if ((*cmd)->lst != NULL)
			big_list_help(cmd);
		(*cmd) = (*cmd)->next;
	}
	*cmd = temp;
	while ((*cmd)->prev)
		*cmd = (*cmd)->prev;
}
