/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:19:17 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/25 18:16:35 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// remove node from lst and poit lst to nxt node
static void	skip_node(t_new **lst, int *skip_flag)
{
	*skip_flag = 1;
	if (!(lst && *lst))
	{
		ft_putstr_fd("What are you doing, there is no list\n", 2);
		return ;
	}
	if ((*lst)->prev != NULL)
		(*lst)->prev->next = (*lst)->next;
	if ((*lst)->next != NULL)
		(*lst)->next->prev = (*lst)->prev;
	*lst = (*lst)->next;
}

// check if input file is valid
static int	input_file_check(char *file_name)
{
	int	fd;

	if (access(file_name, F_OK) == 0)
	{
		if (access(file_name, R_OK) == 0)
		{
			fd = open(file_name, O_RDONLY);
			if (fd == -1)
				return (print_error(file_name, ": Failed to open", 1));
			close(fd);
		}
		else
			return (print_error(file_name, ": Permission denied", 1));
	}
	else
		return (print_error(file_name, ": No such file or directory", 1));
	return (0);
}

// save input redirection name
int	redirect_input(t_new **lst, int *skpflag, int *inflag, char **filestr)
{
	t_new	*temp;

	*filestr = NULL;
	temp = *lst;
	*inflag = 0;
	if (temp && *((temp->token) + 1) == '<')
		*inflag = 1;
	if (temp)
	{
		if (*((temp->token) + 1 + *inflag) != '\0')
			*filestr = (temp->token) + 1 + *inflag;
		else if (temp->next)
		{
			*filestr = temp->next->token;
			skip_node(&temp, skpflag);
		}
		else
			return (print_error("syntax error near unexpected token "
					, temp->token, 258));
		skip_node(&temp, skpflag);
	}
	if ((*inflag == 0) && input_file_check(*filestr) != 0)
		return (1);
	*lst = temp;
	return (0);
}

// check if output is valid
static int	output_file_check(char *file_name, int trunc)
{
	int	fd;

	trunc = (trunc != 0) * O_TRUNC;
	if (access(file_name, F_OK) == 0)
	{
		if (access(file_name, W_OK) == 0)
		{
			fd = open(file_name, O_WRONLY | trunc);
			if (fd == -1)
				return (print_error(file_name, ": Is a directory", 1));
			close(fd);
		}
		else
			return (print_error(file_name, ": Permission denied", 1));
	}
	else
	{
		fd = open(file_name, O_CREAT, 0644);
		if (fd == -1)
			return (print_error(file_name, ": File failed to creat", 1));
		close (fd);
	}
	return (0);
}

// save output redirction name
int	redirect_output(t_new **lst, int *skpflag, int *appendflag, char **filename)
{
	t_new	*temp;

	*filename = NULL;
	temp = *lst;
	if (*((temp->token) + 1) == '>')
		*appendflag = 1;
	else
		*appendflag = 0;
	if (*((temp->token) + 1 + *appendflag) != '\0')
		*filename = (temp->token) + 1 + *appendflag;
	else if (temp->next)
	{
		*filename = temp->next->token;
		skip_node(&temp, skpflag);
	}
	else
		return (print_error("syntax error near unexpected token "
				, temp->token, 258));
	skip_node(&temp, skpflag);
	*lst = temp;
	if (output_file_check(*filename, (*appendflag == 0)) != 0)
		return (1);
	return (0);
}
