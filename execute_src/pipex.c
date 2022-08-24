/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:30:18 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/25 18:11:06 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// create and return a number of pipes
static int	(*create_pipes(int no_of_pipes))[2]
{
	int	(*fd)[2];
	int	i;

	fd = NULL;
	if (no_of_pipes < 1)
		return (NULL);
	fd = malloc(sizeof(*fd) * (no_of_pipes));
	if (fd == NULL)
	{
		print_error("", "malloc failed", 1);
		return (NULL);
	}
	i = 0;
	while (i < no_of_pipes)
	{
		if (pipe(fd[i++]) == -1)
		{
			free(fd);
			return (NULL);
		}
	}
	return (fd);
}

// guide the child step by step until output excution
static int	childmanager(int count, int (*fd)[2], t_new **lst, int *open_fd)
{
	int		new_fd[2];
	int		flag[2];
	char	*ifile_name;
	char	*ofile_name;
	int		errors;

	new_fd[0] = STDIN_FILENO;
	if (count != 0)
		new_fd[0] = fd[count - 1][0];
	new_fd[1] = STDOUT_FILENO;
	if (list_has_pipes(*lst))
		new_fd[1] = fd[count][1];
	errors = set_pipes2(lst, &ifile_name, &ofile_name, flag);
	if (errors)
		return (errors);
	open_fd[1] = hijack_stdout(new_fd[1], ofile_name, *flag, new_fd[1] != 1);
	if (open_fd[1] < 0)
		return (-open_fd[1]);
	if (flag[1] == 0)
		open_fd[0] = hijack_stdin(new_fd[0], ifile_name);
	else if (flag[1] != 0)
		open_fd[0] = adopted_child(new_fd[0], ifile_name);
	if (open_fd[0] < 0)
		return (-open_fd[0]);
	return (errors);
}

// loop and fork until you can't no more
static int	loopy_parent(t_new *lst, char **path, char **env, int (*fd)[2])
{
	int	count;
	int	status;
	int	no_of_pipes;
	int	open_fds[2];

	count = 0;
	open_fds[0] = 0;
	open_fds[1] = 1;
	no_of_pipes = number_of_pipes(lst);
	while (lst)
	{
		if (fork() == 0)
		{
			status = childmanager(count, fd, &lst, open_fds);
			close_pipes(fd, no_of_pipes);
			if (status == 0 && lst != NULL
				&& !(lst->flag == 4 && *(lst->token) == '|'))
				status = child_execute (lst, path, env);
			cleanexit(path, fd, status, open_fds);
		}
		else
			lst = nxt_cmd(lst);
		++count;
	}
	return (0);
}

// parent creating pipes and waiting for children to die
static int	parent_forking5(t_new *lst, char **path, char **env)
{
	int		error;
	int		(*fd)[2];
	int		no_of_pipes;
	int		status;
	int		temp_error;

	temp_error = 0;
	no_of_pipes = number_of_pipes(lst);
	fd = create_pipes(no_of_pipes);
	if (fd == NULL && no_of_pipes != 0)
		return (print_error("", "malloc failed", -1));
	error = loopy_parent(lst, path, env, fd);
	if (error == 0)
	{
		close_pipes(fd, no_of_pipes);
		while (waitpid(-1, &status, 0) > 0)
			if (WEXITSTATUS(status))
				temp_error = WEXITSTATUS(status);
		errno = temp_error;
	}
	free(fd);
	return (error);
}

// excution steps here_doc -> parent builtins -> child builtins
int	excute(t_new *lst, char **env)
{
	char	**path;
	int		i;

	i = 0;
	if (here_doc_input(lst))
		return (0);
	if (has_parentbuiltins(lst))
	{
		errno = builtins(lst, env);
		return (errno);
	}
	if (!env)
		return (0);
	while (env && env[i] && ft_strncmp_p(env[i], "PATH=", 5) != 0)
		++i;
	if (!env || env[i] == NULL)
		path = NULL;
	else
		path = ft_split(env[i] + 5, ':');
	parent_forking5(lst, path, env);
	clear_str_sep(path);
	return (0);
}
