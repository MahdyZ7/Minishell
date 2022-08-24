/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:54:00 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/25 18:25:14 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// hijack stdout to in_file_name or pipe of in_file
int	hijack_stdin(int in_file, char *in_file_name)
{
	if (in_file_name != NULL)
	{
		if (access(in_file_name, F_OK) == -1)
			return (print_error(in_file_name,
					": No such file or directory", -1));
		else if (access(in_file_name, R_OK) == -1)
			return (print_error(in_file_name, ": Permission denied", -1));
		in_file = open(in_file_name, O_RDONLY);
		if (in_file == -1)
			return (print_error(in_file_name, ": File failed to open", -1));
	}
	if (in_file == STDIN_FILENO)
		return (0);
	if (dup2(in_file, STDIN_FILENO) == -1)
	{
		if (in_file_name != NULL)
			close (in_file);
		return (print_error(NULL, ": Failed to hijack stdin", -1));
	}
	return (in_file);
}

// hijack stdout to out_file_name or pipe of out_file
int	hijack_stdout(int out_file, char *out_file_name, int append_flag, int flag)
{
	append_flag = (O_APPEND * (append_flag)) | (O_TRUNC * (!append_flag));
	if (out_file_name != NULL)
	{
		if (access(out_file_name, F_OK) == -1)
			out_file = open(out_file_name, O_CREAT, 0644);
		else if (access(out_file_name, W_OK) == -1)
			return (print_error(out_file_name, ": Permission denied", -1));
		else
			out_file = open(out_file_name, O_WRONLY | append_flag);
		if (out_file == -1)
			return (print_error(out_file_name, ": File failed to open", -1));
	}
	if (flag || out_file_name != NULL)
	{
		if (out_file == STDIN_FILENO)
			return (0);
		if (dup2(out_file, STDOUT_FILENO) == -1)
		{
			if (out_file_name != NULL)
				close (out_file);
			return (print_error(NULL, ": Failed to hijack stdout", -1));
		}
	}
	return (out_file);
}

// loop to know ehich redirection will stand
int	redirect_loop(t_new **lst, char **inputname, char **outputname, int *flag)
{
	t_new	*temp;
	int		skpflag;
	int		err;

	temp = *lst;
	err = 0;
	while (temp && (*(temp->token) != '|' || temp->flag != 4))
	{
		skpflag = 0;
		if (temp && (*(temp->token) == '<' || *(temp->token) == '>')
			&& temp->flag == 4)
		{
			if (*(temp->token) == '<')
				err = redirect_input(&temp, &skpflag, &(flag[1]), inputname);
			else
				err = redirect_output(&temp, &skpflag, flag, outputname);
			if (err)
				return (err);
		}
		if (skpflag != 1)
			temp = temp->next;
	}
	if (temp != NULL)
		temp->next = NULL;
	return (0);
}

// write to input pipe if input id from here doc
int	adopted_child(int in_file, char *here_doc)
{
	int	*fd;

	fd = (int *)malloc(sizeof(*fd) * 2);
	if (ft_lstadd_backhelper(&g_m, fd))
		return (-1);
	if (fd == NULL)
		return (-1);
	if (pipe(fd))
		return (-1);
	ft_putstr_fd(here_doc, fd[1]);
	if (hijack_stdin(fd[0], NULL) < 0)
		return (-1);
	close(fd[0]);
	if (in_file != STDIN_FILENO)
		close(in_file);
	close(fd[1]);
	return (0);
}

// save values of redirection in input params
int	set_pipes2(t_new **lst, char **ifile_name, char **ofile_name, int *flag)
{
	int	errors;

	errors = 0;
	flag[0] = 0;
	flag[1] = 0;
	*ifile_name = NULL;
	*ofile_name = NULL;
	errors = redirect_loop(lst, ifile_name, ofile_name, flag);
	if (errors)
		return (errors);
	find_cmd(lst);
	return (errors);
}
