/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:13:31 by ayassin           #+#    #+#             */
/*   Updated: 2022/08/24 10:46:21 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// make lst point to next comand after pipe
t_new	*nxt_cmd(t_new *lst)
{
	while (lst && (*(lst->token) != '|' || lst->flag != 4))
		lst = lst->next;
	if (lst && *(lst->token) == '|' && lst->flag == 4)
		lst = lst->next;
	return (lst);
}

// count number of pipes in lst
int	number_of_pipes(t_new *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		if (*(lst->token) == '|' && lst->flag == 4)
			++count;
		lst = lst->next;
	}
	return (count);
}

// bool to check if lst has pipes
int	list_has_pipes(t_new *lst)
{
	if (lst == NULL)
		return (0);
	while (lst)
	{
		if (*(lst->token) == '|' && lst->flag == 4)
			return (1);
		lst = lst->next;
	}
	return (0);
}

// close all pipes in (*fd)[2]
void	close_pipes(int (*fd)[2], int no_of_pipes)
{
	int	i;

	i = 0;
	while (i < no_of_pipes)
	{
		close (fd[i][0]);
		close (fd[i][1]);
		++i;
	}
}

// help print error msg when there is a problem
int	print_error(char *problem, char *msg, int errorno)
{
	ft_putstr_fd("minishell$: ", 2);
	ft_putstr_fd(problem, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (errorno);
}
