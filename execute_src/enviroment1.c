/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:31:30 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/27 18:47:48 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// help print env in spical condition of export
static void	ft_putenv_fd(char **env, int fd)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", fd);
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			write(fd, &(env[i][j++]), 1);
		if (env[i][j] == '=')
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(&(env[i][j + 1]), fd);
			ft_putstr_fd("\"", fd);
		}
		write(fd, "\n", 1);
		++i;
	}
}

// print env in spical condition of export
static int	display_env(char **env, char *file_name, int append)
{
	int	fd;

	append = (O_APPEND * (append)) | (O_TRUNC * (!append));
	if (file_name == NULL)
		fd = 1;
	else
		fd = open(file_name, O_WRONLY | append);
	if (fd < 0)
		return (1);
	ft_putenv_fd(env, fd);
	if (file_name && fd > 0)
		close(fd);
	return (0);
}

// change existing env by adding/modifying args in env
int	append_env(char **env, char *args, int j)
{
	if (env[j] && ft_strchr(args, '+') != 0)
	{
		env[j] = ft_strjoin(env[j], ft_strchr(args, '=') + 1);
		if (env[j] == NULL)
			return (print_error("", "malloc failed", 1));
		return (ft_lstadd_backhelper(&g_m, env[j]));
	}
	else if (env[j] && ft_strchr(args, '=') != 0)
	{
		env[j] = ft_strdup(args);
		if (!env[j])
			return (print_error("", "malloc failed", 1));
		return (ft_lstadd_backhelper(&g_m, env[j]));
	}
	else if (!env[j])
		return (append_env1(env, args, j));
	return (0);
}

// loop through args for export function
static int	export_loop(char **env, char **args)
{
	int		prelen;
	int		i;
	int		j;
	int		error;

	i = 1;
	error = 0;
	while (args[i] != NULL)
	{
		if (!valid_varible(args[i]))
		{
			error += print_error(args[i++], ": not a valid identifier", 1);
			continue ;
		}
		prelen = varlen(args[i]);
		j = 0;
		while (env [j] && !(ft_strncmp_p(env[j], args[i], prelen) == 0
				&& (env[j][prelen] == '\0' || env[j][prelen] == '=')))
			++j;
		error += append_env(env, args[i], j);
		++i;
	}
	return (error);
}

// export buitin
int	ft_export(char **args, char **env, char *file_name, int append)
{
	int		error;

	error = 0;
	if (args[1] == NULL)
		error = display_env (env, file_name, append);
	else
		error = export_loop(env, args);
	free(args);
	if (error)
		return (1);
	return (0);
}
