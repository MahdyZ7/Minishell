/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 08:25:36 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:54:02 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// utils for dollar expansion.

int	is_meta(char c)
{
	if (ft_strchr("	 \n|&;()<>$", c))
	{
		return (1);
	}
	return (0);
}

int	is_no_dollar_meta(char c)
{
	if (ft_strchr("<>", c))
	{
		return (1);
	}
	return (0);
}

int	is_no_dollar_meta1(char c)
{
	if (ft_strchr("	 \n&;()", c))
	{
		return (1);
	}
	return (0);
}

int	is_meta_special(char c)
{
	if (ft_strchr("	 \n|&;()<>:?+-=!@#$^{/'}[]|%*,.~", c))
	{
		return (1);
	}
	return (0);
}

int	get_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_meta_special(str[i]))
		i++;
	return (i);
}
