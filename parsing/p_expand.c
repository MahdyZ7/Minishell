/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:27:21 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:52:22 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_meta_special2(char c)
{
	if (ft_strchr("	 \n|&;()<>:?+-=!@#$^{'}[]%*,.~", c))
	{
		return (1);
	}
	if (ft_strchr("1234567890", c))
	{
		return (1);
	}
	return (0);
}

int	get_expanded_list_help(t_list **lst, t_list *temp, char *str, int i)
{
	int	flag;

	flag = 0;
	if (is_no_dollar_meta(str[i]))
		flag = ft_expand4(lst, temp, str + i);
	else if (is_meta_pipe(str[i]))
		flag = ft_expand7(lst, temp, str + i);
	else if (is_no_dollar_meta1(str[i]))
		flag = ft_expand5(lst, temp, str + i);
	else
		flag = ft_expand6(lst, temp, str + i);
	return (flag);
}

t_list	*get_expanded_list(char *str, char **env)
{
	int		i;
	int		flag;
	t_list	*lst;
	t_list	*temp;

	i = 0;
	flag = 0;
	lst = NULL;
	while (str[i])
	{
		flag = 0;
		temp = NULL;
		if (str[i] == '$' && (str[i + 1] == '?' || str[i + 1] == '$'))
			i += ft_expand1(&lst, temp, str[i + 1]);
		else if (str[i] == '$' && (!str[i + 1] || is_meta_special2(str[i + 1])))
			i += ft_expand2(&lst, temp, str[i + 1]) + 1;
		else if (str[i] == '$')
			i += ft_expand3(&lst, temp, str + i + 1, env)
				+ get_strlen(str + i + 1) + 1;
		else
			flag = get_expanded_list_help(&lst, temp, str, i);
		i = ft_move_string(str, i, flag);
	}
	return (lst);
}

char	*get_expanded_string(char *str, char **env)
{
	char	*s;
	t_list	*lst;

	s = "";
	lst = get_expanded_list(str, env);
	while (lst)
	{
		ft_strjoin_ps(&s, (char *)lst->content, 0);
		lst = lst->next;
	}
	return (s);
}
