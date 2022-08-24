/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:38:06 by ayassin           #+#    #+#             */
/*   Updated: 2022/08/09 18:17:36 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// transform lst (until a pipe apears) into a 2D array 
char	**args_array(t_new *lst)
{
	int		arg_count;
	t_new	*temp;
	char	**args;
	int		i;

	arg_count = 0;
	temp = lst;
	while (temp && (temp->flag != 4 || !ft_strchr("<>|", *(temp->token))
			|| *(temp->token) == 0))
	{
		++arg_count;
		temp = temp->next;
	}
	args = (char **)malloc(sizeof(*args) * (arg_count + 1));
	if (args == NULL)
		return (NULL);
	i = 0;
	temp = lst;
	while (i < arg_count)
	{
		args[i++] = temp->token;
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

// switch function for parent buitins
int	buitin_switch(t_new *lst, char **env, char *file_name, int append	)
{
	char	**args;

	args = args_array(lst);
	if (args == NULL)
		return (1);
	ft_tolower_str(lst->token);
	if (lst->token && (ft_strncmp_p(lst->token, "cd", 3) == 0))
		return (ft_chdir(args, env));
	else if (lst->token && (ft_strncmp_p(lst->token, "export", 7) == 0))
		return (ft_export(args, env, file_name, append));
	else if (lst->token && (ft_strncmp_p(lst->token, "unset", 6) == 0))
		return (ft_unset(args, env));
	else if (lst->token && (ft_strncmp_p(lst->token, "exit", 5) == 0))
		return (ft_exit(args, 0));
	else if (ft_strchr(lst->token, '=') && valid_varible(lst->token))
		return (1);
	return (1);
}

// switch function for child buitins
static int	child_buitin_switch(char *cmd, char **args, char **env)
{
	int	value;

	value = -1;
	if (cmd && ft_strncmp_p(cmd, "echo", 5) == 0)
		value = ft_echo(args);
	else if (cmd && ft_strncmp_p(cmd, "pwd", 4) == 0)
		value = ft_pwd(args);
	else if (cmd && ft_strncmp_p(cmd, "env", 4) == 0)
		value = ft_env(env, args);
	else if (cmd && (ft_strncmp_p(cmd, "cd", 3) == 0))
		value = ft_chdir(args, env);
	else if (cmd && (ft_strncmp_p(cmd, "export", 7) == 0))
		value = ft_export(args, env, NULL, 0);
	else if (cmd && (ft_strncmp_p(cmd, "unset", 6) == 0))
		value = ft_unset(args, env);
	else if (cmd && (ft_strncmp_p(cmd, "exit", 5) == 0))
		value = ft_exit(args, 1);
	if (value != -1)
	{
		close (1);
		close (3);
		free (cmd);
	}
	return (value);
}

// try and excute function in each and every path given
static int	child_loop(char **path, char **args, char **env, char *clone_cmd)
{
	int	i;

	i = 0;
	while (path && path[i])
	{
		if (ft_strjoin_ms(&(path[i]), "/") < 0
			|| ft_strjoin_ms(&(path[i]), clone_cmd) < 0)
			return (1);
		execve(path[i], args, env);
		++i;
	}
	return (0);
}

// try to excute command in a child
int	child_execute(t_new *lst, char **path, char **env)
{
	char	**args;
	int		temp_return;
	char	*clone_cmd;

	clone_cmd = ft_strdup(lst->token);
	if (!clone_cmd)
		return (print_error("", "malloc failed", 1));
	ft_tolower_str(clone_cmd);
	args = args_array(lst);
	if (args == NULL)
		return (print_error("", "malloc failed", 1));
	temp_return = child_buitin_switch(clone_cmd, args, env);
	if (temp_return != -1)
		return (temp_return);
	temp_return = child_loop(path, args, env, clone_cmd);
	if (clone_cmd && temp_return == 0 && ft_strchr(clone_cmd, '/'))
		execve(clone_cmd, args, env);
	free(clone_cmd);
	free(args);
	if (temp_return)
		return (1);
	else if (lst->token && ft_strchr(lst->token, '/'))
		return (print_error(lst->token, ": No such file or directory", 127));
	else
		return (print_error(lst->token, ": command not found", 127));
}
