/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redirection2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:55:44 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/16 14:38:05 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//------------------------------------------------------------------
//----------------------------Error Handling------------------------
//------------------------------------------------------------------

// int	is_rpd(char c)
// {
// 	if (ft_strchr("<>|/", c))
// 		return (1);
// 	return (0);
// }

int	find_lderror(char *str, t_new *cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			if (str[i + 2] == '|' || (!str[i + 2] && !cmd->next))
				return (ft_putstr_fd1("Wrong syntax \n", 2));
			else if (str[i + 2] == '<' || str[i + 2] == '>')
				return (ft_putstr_fd1("Wrong syntax \n", 2));
		}
		else if (str[i] == '>' && str[i + 1] == '<')
			return (ft_putstr_fd1("Wrong syntax \n", 2));
		else if (str[i] == '>' && str[i + 1] == '|')
			return (ft_putstr_fd1("Wrong syntax \n", 2));
		i++;
	}
	return (0);
}

int	find_rderror(char *str, t_new *cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			if (str[i + 2] == '|' || (!str[i + 2] && !cmd->next))
				return (ft_putstr_fd1("Wrong syntax \n", 2));
			else if (str[i + 2] == '<' || str[i + 2] == '>')
				return (ft_putstr_fd1("Wrong syntax \n", 2));
		}
		else if (str[i] == '<' && str[i + 1] == '>')
			return (ft_putstr_fd1("Wrong syntax \n", 2));
		else if (str[i] == '<' && str[i + 1] == '|')
			return (ft_putstr_fd1("Wrong syntax \n", 2));
		if (str[i] == '>' || str[i] == '<')
			if (!str[i + 1] && !cmd->next)
				return (ft_putstr_fd1("Wrong syntax \n", 2));
		i++;
	}
	return (0);
}

int	find_perror_help(char *str, t_new *cmd, int i)
{
	if (str[i + 1] == '|' || (!str[i + 1] && !cmd->next))
		return (2);
	else if (str[i + 1] == '\0' && cmd->next)
	{
		if (cmd->next->token[0] == '|')
			return (2);
	}
	else if (str[i + 1] == '<' || str[i + 1] == '>')
	{
		if (is_meta_pipe(str[i + 2]))
			if (!str[i + 2])
				return (2);
	}
	return (0);
}

int	find_perror(char *str, t_new *cmd)
{
	int	i;

	i = 0;
	if (str[i] == '|' && !cmd->prev)
		return (ft_putstr_fd1("Wrong syntax \n", 2));
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (find_perror_help(str, cmd, i))
				return (ft_putstr_fd1("Wrong syntax \n", 2));
		}
		i++;
	}
	return (0);
}

int	syntax_error(t_new *cmd)
{
	int	flag;

	flag = 0;
	while (cmd != NULL)
	{
		if (cmd->flag == 3)
		{
			flag += find_rderror(cmd->token, cmd);
			if (!flag)
				flag += find_lderror(cmd->token, cmd);
			if (!flag)
				flag += find_perror(cmd->token, cmd);
		}
		cmd = cmd->next;
	}
	if (flag)
		errno = 258;
	return (flag);
}
