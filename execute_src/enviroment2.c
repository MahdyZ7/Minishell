/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:12:06 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/27 18:13:47 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*atoi function that allows overflows */
static int	minishell_atoi(char *str)
{
	int	i;
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		++i;
	}
	if (str[i])
		return (0);
	return (num * sign);
}

// help update shell level
static int	update_shlvlhelper(char **env, int i, int level)
{
	int		error;
	char	*temp;
	char	*temp2;

	error = 0;
	if (level < 0)
			level = 0;
	else if (level > 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(level, 2);
		ft_putstr_fd(") too high, reseting to 1\n", 2);
		level = 1;
	}
	temp = ft_itoa(level);
	if (temp == NULL)
		return (print_error("", "malloc failed", 1));
	temp2 = ft_strjoin("SHLVL=", temp);
	if (temp2 != NULL)
		error = append_env(env, temp2, i);
	free (temp);
	if (temp2 == NULL)
		return (print_error("", "malloc failed", 1));
	free(temp2);
	return (error);
}

// update shell level in env
int	update_shlvl(char **env, char *var)
{
	int		i;
	int		level;
	char	*temp;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (env [i] && !(ft_strncmp_p(env[i], var, len) == 0
			&& (env[i][len] == '\0' || env[i][len] == '=')))
			++i;
	if (env[i])
	{
		level = 1
			+ minishell_atoi(&(env[i][5 + (ft_strchr(env[i], '=') != 0)]));
		if (level == 1000)
			return (append_env(env, "SHLVL=", i));
		return (update_shlvlhelper(env, i, level));
	}
	temp = ft_strdup("SHLVL=1");
	if (temp == NULL)
		return (print_error("", "malloc failed", 1));
	return (append_env(env, temp, i));
}

// check variable name length
int	varlen(char *var)
{
	if (ft_strchr(var, '+') != 0)
		return (ft_strchr(var, '+') - var);
	else if (ft_strchr(var, '=') != 0)
		return (ft_strchr(var, '=') - var);
	else
		return (ft_strlen(var));
}

// add varable to new malloced env
int	append_env1(char **env, char *args, int j)
{
	char	**new_env;
	char	*pluspos;

	new_env = (char **)malloc(sizeof(*env) * (j + 2));
	if (!new_env)
		return (print_error("", "malloc failed", 1));
	if (ft_lstadd_backhelper(&g_m, new_env))
		return (1);
	if (cpynewenv(new_env, env))
		return (1);
	env[j] = args;
	pluspos = ft_strchr(env[j], '+');
	while (pluspos && *pluspos)
	{
		*pluspos = *(pluspos + 1);
		++pluspos;
	}
	env[j + 1] = NULL;
	return (0);
}
