/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 18:31:11 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/27 09:49:32 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// go to root folder
static void	go_to_headdir(void)
{
	char	*new_loc;
	char	*temp_loc;

	new_loc = NULL;
	temp_loc = NULL;
	while (ft_strlen(new_loc) != ft_strlen(temp_loc) || temp_loc == NULL)
	{
		if (new_loc)
			free(new_loc);
		new_loc = getcwd(NULL, 0);
		chdir("..");
		if (temp_loc)
			free(temp_loc);
		temp_loc = getcwd(NULL, 0);
	}
	if (temp_loc)
		free(temp_loc);
	if (new_loc)
		free(new_loc);
}

// help update PWD and OLDPWD in env
static int	update_envpwd_helper(char *old_loc, char *var, char **env, int i)
{
	int		error;
	char	*tempstr;

	error = 0;
	tempstr = NULL;
	tempstr = ft_strdup(var);
	if (!tempstr)
		return (print_error("", "malloc failed", 1));
	error = ft_strjoin_ms(&tempstr, "=");
	env[i] = tempstr;
	if (old_loc)
		tempstr = old_loc;
	else
		tempstr = getcwd(NULL, 0);
	error += ft_strjoin_ms(&env[i], tempstr);
	if (!tempstr)
		error += 1;
	if (!old_loc && tempstr)
		free (tempstr);
	if (ft_lstadd_backhelper(&g_m, env[i]) != 0)
		return (1);
	return (error);
}

// update PWD and OLDPWD in env
static int	update_envpwd(char *old_loc, char *var, char **env)
{
	int		i;
	int		error;
	int		len;

	i = 0;
	error = 0;
	len = ft_strlen(var);
	while (env [i] && !(ft_strncmp_p(env[i], var, len) == 0
			&& (env[i][len] == '\0' || env[i][len] == '=')))
			++i;
	if (env[i])
		error = update_envpwd_helper(old_loc, var, env, i);
	return (error);
}

// go to an absilute directory
static int	ft_chdir_abs(char **args, char **env, char	*old_loc)
{
	char	*home;

	home = get_home(env);
	if (home && *home != '\0')
	{
		go_to_headdir();
		if (chdir(home) == -1)
		{
			chdir(old_loc);
			return (print_error(home, ": No such file or directory", 1));
		}
		if (args[1] && args[1][1] != '\0' && chdir(&args[1][2]) == -1)
		{
			go_to_headdir();
			chdir(old_loc);
			return (print_error(&args[1][1], ": No such file or directory", 1));
		}
	}
	else
		return (print_error("cd: ", "HOME not set", 1));
	return (0);
}

// cd builtin function
int	ft_chdir(char **args, char **env)
{
	char	*old_loc;
	int		error;

	error = 0;
	old_loc = getcwd(NULL, 0);
	if (args[1] == NULL || args[1][0] == '~')
		error = ft_chdir_abs(args, env, old_loc);
	else if (chdir(args[1]) == -1)
	{
		if (access(args[1], F_OK))
			print_error(args[1], ": No such file or directory", 1);
		else if (access(args[1], X_OK))
			print_error(args[1], ": Permission denied", 1);
		else
			print_error(args[1], ": Not a directory", 1);
		error = 1;
	}
	if (error == 0)
		error = update_envpwd(NULL, "PWD", env);
	if (error == 0)
		error = update_envpwd(old_loc, "OLDPWD", env);
	if (old_loc)
		free(old_loc);
	free(args);
	return (error);
}
