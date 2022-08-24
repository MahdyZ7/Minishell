/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expand2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:39:58 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:52:31 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit2(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (ft_strchr("!@", c))
		return (1);
	return (0);
}

char	*get_meta(char *str)
{
	int		i;
	char	*s;
	t_list	*tmp;

	i = 0;
	while (str[i] && is_no_dollar_meta(str[i]))
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	tmp = ft_lstnew((void *)(s));
	ft_lstadd_back(&g_m, tmp);
	i = 0;
	while (str[i] && is_no_dollar_meta(str[i]))
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*get_meta1(char *str)
{
	int		i;
	char	*s;
	t_list	*tmp;

	i = 0;
	while (str[i] && is_no_dollar_meta1(str[i]))
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	tmp = ft_lstnew((void *)(s));
	ft_lstadd_back(&g_m, tmp);
	i = 0;
	while (str[i] && is_no_dollar_meta1(str[i]))
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_expand1(t_list **lst, t_list *temp, char c)
{
	t_list	*tmp;
	char	*s;

	s = NULL;
	if (c == '?')
		s = ft_itoa(errno);
	else if (c == '$')
		s = ft_strdup("");
	if (s)
		ft_lstadd_back(&g_m, ft_lstnew((void *)(s)));
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
	return (2);
}

int	ft_expand2(t_list **lst, t_list *temp, char c)
{
	int		k;
	char	*s;

	k = 0;
	s = NULL;
	if ((is_meta_special2(c) && !ft_isdigit2(c)) || !c)
	{
		s = ft_strdup("");
		temp = ft_lstnew((void *)s);
		k = 0;
	}
	else if (is_meta_special2(c) && ft_isdigit2(c))
	{
		s = ft_strdup("");
		temp = ft_lstnew((void *)s);
		k = 1;
	}
	if (s)
		ft_lstadd_back(&g_m, ft_lstnew((void *)(s)));
	ft_lstadd_back(lst, temp);
	ft_lstadd_back(&g_m, ft_lstnew((void *)(temp)));
	return (k);
}

	// if (!c)
	// {
	// 	s = ft_strdup("$");
	// 	temp = ft_lstnew((void *)s);
	// }