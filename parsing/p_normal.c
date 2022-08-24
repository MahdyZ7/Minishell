/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_normal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:16:26 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:53:41 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// handling words without quotes
int	get_word_len(char *line)
{
	int	len;

	len = 0;
	while (ft_isspace(*line) && *line)
		line++;
	if (!*line)
		return (-1);
	while (!ft_isspace(*line) && *line && is_quote(*line))
	{
		line++;
		len++;
	}
	return (len);
}

// get normal word
char	*normal_word(char *line)
{
	char	*word;
	t_list	*tmp;
	int		i;
	int		len;

	len = get_word_len(line);
	word = malloc(sizeof(char) * (len + 1));
	tmp = ft_lstnew((void *)(word));
	ft_lstadd_back(&g_m, tmp);
	i = 0;
	while (line[i] && is_quote(line[i]))
	{
		if (ft_isspace(line[i]))
			break ;
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	check_word_for_parsing(char *line)
{
	if (*(line) == '"')
		return (1);
	else if (*(line) == 39)
		return (2);
	else
		return (3);
}

char	*get_word(t_info *info, char *line)
{
	char	*word;

	info->flag = 1;
	word = NULL;
	if (info->e_flag)
		return (NULL);
	while (ft_isspace(*line) && *line)
		line++;
	info->w_flag = check_word_for_parsing(line);
	if (info->w_flag == 3)
		word = normal_word(line);
	else if (info->w_flag == 1)
		word = quoted_word(++line, '"');
	else if (info->w_flag == 2)
		word = quoted_word(++line, 39);
	return (word);
}

int	normal_lexer_help(t_new **pars, t_info *info, char *str, int wc)
{
	char	*temp1;
	t_list	*tmp;

	temp1 = get_word(info, str);
	if (!wc && *str && temp1)
	{
		(*pars) = malloc(sizeof(t_new));
		tmp = ft_lstnew((void *)(*pars));
		ft_lstadd_back(&g_m, tmp);
		lst_add_new(pars, temp1, info);
		wc++;
	}
	else if (*str && temp1)
	{
		if (ft_isspace(*(str - 1)))
			lst_add_back(pars, temp1, info, 1);
		else
			lst_add_back(pars, temp1, info, -1);
		wc++;
	}
	return (wc);
}

// void	normal_lexer(t_new **pars, t_info *info, char *str)
// {
// 	int		wc;
// 	char	*temp;
// 	int		flag;

// 	wc = 0;
// 	flag = 1;
// 	while (*str)
// 	{
// 		info->w_flag = 0;
// 		while (*str && ft_isspace(*str))
// 			str++;
// 		wc = normal_lexer_help(pars, info, str, wc);
// 		if (*str == '"')
// 			temp = go_past_quotes(++str, '"', &flag);
// 		else if (*str == 39)
// 			temp = go_past_quotes(++str, 39, &flag);
// 		while (*str && !ft_isspace(*str) && flag && is_quote(*str))
// 			str++;
// 		if (!flag)
// 		{
// 			str = temp;
// 			flag = 1;
// 		}
// 	}
// }
