/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:58:25 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:53:47 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// For handling the quotes
#include "../minishell.h"

char	*quote_count_help(char *temp2)
{
	int	i;

	i = 0;
	while (temp2[i])
	{
		if (temp2[i] == '"')
		{
			i++;
			while (temp2[i] != '"' && temp2[i])
				temp2[i++] = 'a';
			if (temp2[i])
				i++;
		}
		else if (temp2[i] == 39)
		{
			i++;
			while (temp2[i] != 39 && temp2[i])
				temp2[i++] = 'a';
			if (temp2[i])
				i++;
		}
		else
			i++;
	}
	return (temp2);
}

void	quote_counter(char *line, t_info *info)
{
	int		c;
	int		i;
	int		d;
	char	*temp2;
	t_list	*tmp;

	c = 0;
	d = 0;
	temp2 = ft_strdup(line);
	tmp = ft_lstnew((void *)(temp2));
	ft_lstadd_back(&g_m, tmp);
	temp2 = quote_count_help(temp2);
	i = 0;
	while (temp2[i])
	{
		if (temp2[i] == '"')
			c++;
		else if (temp2[i] == 39)
			d++;
		i++;
	}
	if (c % 2 || d % 2)
		info->q_flag = 1;
}

int	ft_strlen_ch(char *line, char c)
{
	int	len;

	len = 0;
	while (*line != c && *line)
	{
		len++;
		line++;
	}
	return (len);
}

// get the quoted word
char	*quoted_word(char *line, char ch)
{
	int		i;
	int		len;
	char	*s;
	t_list	*tmp;

	i = 0;
	len = ft_strlen_ch(line, ch);
	if (len >= 0)
	{
		s = malloc(sizeof(char) * (len + 1));
		tmp = ft_lstnew((void *)(s));
		ft_lstadd_back(&g_m, tmp);
		while (line[i] && line[i] != ch)
		{
			s[i] = line[i];
			i++;
		}
		s[i] = '\0';
		return (s);
	}
	return (NULL);
}

// move the pointer after the quote
char	*go_past_quotes(char *s, char ch, int *flag)
{
	*flag = 0;
	while (*s != ch && *s)
		s++;
	if (*s == ch)
		s++;
	return (s);
}
