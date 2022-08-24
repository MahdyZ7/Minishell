/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_list_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:22:36 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:53:04 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_add_new(t_new **pars, char *str, t_info *info)
{
	(*pars)->token = str;
	(*pars)->next = NULL;
	(*pars)->prev = NULL;
	(*pars)->lst = NULL;
	(*pars)->es = NULL;
	if (info)
	{
		if (info->w_flag == 1)
			(*pars)->flag = 1;
		else if (info->w_flag == 3)
			(*pars)->flag = 3;
		else if (info->w_flag == 2)
			(*pars)->flag = 2;
	}
}

void	get_info(t_info *info, t_new *temp)
{
	if (info->w_flag == 1)
		temp->flag = 1;
	else if (info->w_flag == 3)
		temp->flag = 3;
	else if (info->w_flag == 2)
		temp->flag = 2;
}

void	lst_add_back(t_new **pars, char *str, t_info *info, int flag)
{
	t_new	*par;
	t_new	*temp;
	t_list	*tmp;

	par = *pars;
	while ((*pars)->next)
		(*pars) = (*pars)->next;
	temp = malloc(sizeof(t_new));
	tmp = ft_lstnew((void *)(temp));
	ft_lstadd_back(&g_m, tmp);
	temp->token = str;
	temp->es = NULL;
	temp->lst = NULL;
	temp->s_flag = flag;
	if (info)
		get_info(info, temp);
	(*pars)->next = temp;
	temp->next = NULL;
	temp->prev = (*pars);
	(*pars) = par;
}
