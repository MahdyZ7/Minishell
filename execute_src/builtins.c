/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:45:02 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/25 17:23:38 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//check if args[i] is a -n flag. it stops when arg[*i] is not a flag
static int	ft_echoflag(char **args, int *i)
{
	char	flag;
	int		j;

	flag = 1;
	*i = 1;
	while (args[*i] && args[*i][0] == '-')
	{
		j = 1;
		while (args[*i][j] && args[*i][j] == 'n')
			++j;
		if (!args[*i][j] && args[*i][j - 1] == 'n')
			flag = 0;
		else
			break ;
		*i = *i + 1;
	}
	return (flag);
}

// echo function for strings in array args
int	ft_echo(char **args)
{
	char	flag;
	int		i;

	i = 1;
	flag = ft_echoflag(args, &i);
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		++i;
	}
	if (flag)
		ft_putstr_fd("\n", 1);
	free(args);
	return (0);
}

// print path to current directory
int	ft_pwd(char **args)
{
	char	*my_dir;

	my_dir = getcwd(NULL, 0);
	ft_printf("%s\n", my_dir);
	if (my_dir)
		free(my_dir);
	free(args);
	return (0);
}

// print env regardless of args
int	ft_env(char **env, char **args)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '=') != 0)
			ft_printf("%s\n", env[i]);
		++i;
	}
	free(args);
	return (0);
}

// return HOME value from env if present
char	*get_home(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp_p(env[i], "HOME=", 5) == 0)
			return (&env[i][5]);
		++i;
	}
	return (NULL);
}
