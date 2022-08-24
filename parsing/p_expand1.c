/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expand1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:34:33 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:52:27 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_dollar_path_help(char *s, char **env, int len)
{
	char	*s1;
	int		i;

	i = 0;
	s1 = NULL;
	while (env[i] && len)
	{
		s1 = ft_strnstr(env[i], s, len);
		if (s1)
		{
			s1 = s1 + len;
			if (*s1 == '=')
				s1++;
			else
				return ("");
			break ;
		}
		i++;
	}
	if (!s1)
		s1 = "";
	return (s1);
}

char	*get_dollar_path(char *str, char **env)
{
	char	*s;
	int		len;
	t_list	*tmp;

	len = 0;
	len = get_strlen(str);
	s = NULL;
	if (len)
	{
		s = ft_substr(str, 0, len);
		tmp = ft_lstnew((void *)(s));
		ft_lstadd_back(&g_m, tmp);
	}
	return (get_dollar_path_help(s, env, len));
}

int	is_meta_pipe(char c)
{
	if (ft_strchr("|", c))
	{
		return (1);
	}
	return (0);
}

char	*get_meta_pipe(char *str)
{
	int		i;
	char	*s;
	t_list	*tmp;

	i = 0;
	while (str[i] && is_meta_pipe(str[i]))
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	tmp = ft_lstnew((void *)(s));
	ft_lstadd_back(&g_m, tmp);
	i = 0;
	while (str[i] && is_meta_pipe(str[i]))
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*get_str(char *str)
{
	int		i;
	char	*s;
	t_list	*tmp;

	i = 0;
	while (str[i] && !is_meta(str[i]))
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	tmp = ft_lstnew((void *)(s));
	ft_lstadd_back(&g_m, tmp);
	i = 0;
	while (str[i] && !is_meta(str[i]))
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
