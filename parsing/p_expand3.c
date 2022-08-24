/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expand3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:43:44 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:52:36 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_expand4(t_list **lst, t_list *temp, char *str)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = ft_lstnew((void *)get_meta(str));
		tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)get_meta(str));
		ft_lstadd_back(lst, temp);
		tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
	return (1);
}

int	ft_expand5(t_list **lst, t_list *temp, char *str)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = ft_lstnew((void *)get_meta1(str));
		tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)get_meta1(str));
		ft_lstadd_back(lst, temp);
		tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
	return (2);
}

int	ft_expand6(t_list **lst, t_list *temp, char *str)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = ft_lstnew((void *)get_str(str));
		tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)get_str(str));
		ft_lstadd_back(lst, temp);
		tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
	return (3);
}

int	ft_expand7(t_list **lst, t_list *temp, char *str)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = ft_lstnew((void *)get_meta_pipe(str));
		tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)get_meta_pipe(str));
		ft_lstadd_back(lst, temp);
		tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
	return (4);
}

int	ft_move_string(char *str, int i, int flag)
{
	if (flag == 1)
		while (str[i] && is_no_dollar_meta(str[i]))
			i++;
	else if (flag == 2)
		while (str[i] && is_no_dollar_meta1(str[i]))
				i++;
	else if (flag == 3)
		while (str[i] && !is_meta(str[i]))
			i++;
	else if (flag == 4)
		while (str[i] && is_meta_pipe(str[i]))
				i++;
	return (i);
}
