/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expand4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:24:15 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:52:40 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_expand3(t_list **lst, t_list *temp, char *str, char **env)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = ft_lstnew((void *)get_dollar_path(str, env));
		tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)get_dollar_path(str, env));
		ft_lstadd_back(lst, temp);
		tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
	return (0);
}

int	no_redirection(char *str)
{
	if (*str == '<' || *str == '>' || *str == '|')
		return (0);
	return (1);
}

void	add_to_list(t_list **lst, void *s)
{
	t_list	*tmp;
	t_list	*temp;

	if (!*lst)
	{
		*lst = ft_lstnew((void *)s);
		tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)s);
		ft_lstadd_back(lst, temp);
		tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
}

void	move_list(t_list **lst, char **s)
{
	while (*lst)
	{
		if (no_redirection((*lst)->content))
			ft_strjoin_ps(s, (char *)(*lst)->content, 0);
		else
			break ;
		*lst = (*lst)->next;
	}
}

t_list	*get_expanded_string2(char *str, char **env)
{
	char	*s;
	t_list	*lst;
	t_list	*lst1;

	s = "";
	lst = get_expanded_list(str, env);
	lst1 = NULL;
	while (lst)
	{
		if (no_redirection(lst->content) && lst)
		{
			move_list(&lst, &s);
			add_to_list(&lst1, s);
		}
		else if (lst)
		{
			add_to_list(&lst1, lst->content);
			lst = lst->next;
			s = "";
		}
	}
	return (lst1);
}
