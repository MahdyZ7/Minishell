/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_assign_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:32:04 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:52:21 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var(char *line, t_info *info)
{
	int	c;

	c = 0;
	while (*line && ft_isspace(*line))
		line++;
	if (*line == '=')
	{
		info->e_flag = 1;
		return (0);
	}
	else
	{
		if (!is_quote(*line))
			return (0);
		while (*line)
		{
			if (*line == '=')
				c++;
			line++;
		}
		if (c)
			return (1);
	}
	return (0);
}

int	get_vars(char *line)
{
	int	len;

	len = 0;
	while (*line != '=')
	{
		len++;
		line++;
	}
	return (len);
}

int	get_len(char *line)
{
	int	len;

	len = 0;
	while (*line)
	{
		len++;
		line++;
	}
	return (len);
}

char	*get_key(char *line)
{
	int		len;
	int		i;
	char	*temp;

	len = 0;
	len = get_vars(line);
	if (len)
	{
		temp = malloc(sizeof(char) * (len + 1));
		ft_lstadd_back(&g_m, ft_lstnew((void *)(temp)));
	}
	i = 0;
	while (line[i] != '=' && line[i])
	{
		temp[i] = line[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*get_value(char *line)
{
	int		len;
	char	*temp;
	int		i;

	len = 0;
	len = get_len(line);
	if (len)
	{
		temp = malloc(sizeof(char) * (len + 1));
		ft_lstadd_back(&g_m, ft_lstnew((void *)(temp)));
	}
	i = 0;
	while (line[i])
	{
		temp[i] = line[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
