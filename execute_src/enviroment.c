/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:44:36 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/27 18:23:34 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// copy strings in env to newenv
int	cpynewenv(char **new_env, char **env)
{
	int		count;

	count = 0;
	if (!env)
		return (0);
	while (env[count])
	{
		new_env[count] = ft_strdup(env[count]);
		if (new_env[count] == NULL)
			return (print_error("", "malloc failed", 1));
		if (ft_lstadd_backhelper(&g_m, new_env[count]))
			return (1);
		++count;
	}
	new_env[count] = NULL;
	*env = *new_env;
	return (0);
}

// create new env that is a copy of env
int	setnewenv(char **env)
{
	int		count;
	char	**new_env;

	count = 0;
	new_env = NULL;
	while (env && env[count])
		++count;
	if (count)
	{
		new_env = (char **)malloc((sizeof(*new_env) + 1) * count);
		if (!new_env)
			return (print_error("", "malloc failed", 1));
		if (ft_lstadd_backhelper(&g_m, new_env))
			return (1);
		return (cpynewenv(new_env, env));
	}
	return (0);
}

// is var a valid variable name
int	valid_varible(char *var)
{
	int	i;

	i = 0;
	if (!var || !*var || !(ft_isalpha(*var) || *var == '_'))
		return (0);
	while (var[i] && !(var[i] == '=' || var[i] == '+'))
	{
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (0);
		++i;
	}
	if (var[i] == '+' && var[i + 1] != '=')
		return (0);
	return (1);
}

// help unset varables in args from env
void	ft_unset_helper(char *args, char **env)
{
	int	i;
	int	prelen;

	i = 0;
	prelen = ft_strlen(args) + 1;
	while (env [i] && !((ft_strncmp_p(env[i], args, prelen) == '=')
			|| (ft_strncmp_p(env[i], args, prelen) == 0
				&& ft_strchr(env[i], '=') == NULL)))
		++i;
	while (env[i] && env [i + 1])
	{
		env[i] = env[i + 1];
		++i;
	}
	env[i] = NULL;
}

// unset varabils in args from enviroment
int	ft_unset(char **args, char **env)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (args[i] != NULL)
	{
		if (!valid_varible(args[i]) || ft_strchr(args[i], '=') != 0)
		{
			error = print_error(args[i++], ": not a valid identifier", 1);
			continue ;
		}
		ft_unset_helper(args[i], env);
		++i;
	}
	free(args);
	return (error);
}
