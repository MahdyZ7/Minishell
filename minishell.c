/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:19:39 by ayassin           #+#    #+#             */
/*   Updated: 2022/08/16 14:46:39 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_m;

static void	main_helper(t_info *info, char **env, char *line, t_new *cmd);
static void	main_loop(t_info *info, char **env);

int	main(int ac, char **av, char **env)
{
	t_info	*info;

	(void) ac;
	(void) av;
	g_m = NULL;
	if (ft_lstadd_backhelper(&g_m, NULL) != 0)
		return (1);
	signals();
	info = malloc(sizeof(t_info));
	if (info == NULL)
		cleanexit(NULL, NULL, print_error("", "malloc failed", 1), NULL);
	if (ft_lstadd_backhelper(&g_m, info) != 0)
		cleanexit(NULL, NULL, 1, NULL);
	if (setnewenv(env))
		cleanexit(NULL, NULL, 1, NULL);
	if (update_shlvl(env, "SHLVL"))
		cleanexit(NULL, NULL, 1, NULL);
	info->flag = 1;
	info->e_flag = 0;
	main_loop(info, env);
	cleanexit(NULL, NULL, 0, NULL);
	return (0);
}

static void	main_helper(t_info *info, char **env, char *line, t_new *cmd)
{
	if (!line)
		cleanexit(NULL, NULL, 0, NULL);
	else if (*line == '\0')
		;
	else if (!ft_strncmp(line, "clear", 6))
		ft_clearscreen();
	else if (!info->q_flag)
	{
		normal_lexer(&cmd, info, line);
		find_dollar_presence(cmd);
		find_redirection_presence(cmd);
		dollar_expansion(cmd, env);
		make_all_zero(cmd);
		if (cmd && !syntax_error(cmd))
		{
			make_big_list(&cmd);
			ft_lst_join(cmd);
			find_redirection_presence(cmd);
			excute (cmd, env);
		}
	}
	else if (info->q_flag)
		errno = print_error("wrong syntax", "", 258);
}

static void	main_loop(t_info *info, char **env)
{
	int		err;
	char	*line;
	t_new	*cmd;

	line = NULL;
	cmd = NULL;
	while (1)
	{
		info->e_flag = 0;
		info->q_flag = 0;
		err = errno;
		line = ft_readline();
		if (!errno)
			errno = err;
		if (line)
			add_history(line);
		else
		{
			ft_putstr_fd("exit\n", 2);
			cleanexit(NULL, NULL, 0, NULL);
		}
		quote_counter(line, info);
		main_helper(info, env, line, cmd);
		free (line);
	}
}
