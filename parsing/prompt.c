/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:55:02 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/15 21:45:44 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_readline(void)
{
	char	*line;

	line = readline("minishell$ ");
	return (line);
}

void	ft_clearscreen(void)
{
	ft_putstr_fd("\e[1;1H\e[2J", 2);
}

// void	ft_clearscreen(void)
// {
// 	// char	*buf;
// 	char	*str;

// 	// buf = (char *)malloc(sizeof(char) * (ft_strlen(getenv("TERM")) + 1));
// 	// g_m = ft_lstnew((void *)buf);
// 	tgetent(buf, getenv("TERM"));
// 	str = tgetstr("cl", NULL);
// 	printf("%s", str);
// 	// printf("");
// }

// for printing purposes
void	lst_print(t_new *pars)
{
	while (pars != NULL)
	{
		printf("<token: %s> <flag: %d> <d_flag: %d> \
		<s_flag: %d> <l_flag: %d> <l2_flag: %d> \
			<r_flag: %d> <r2_flag: %d> <dq_flag: %d>",
			pars->token, pars->flag, pars->d_flag, pars->s_flag, pars->l_flag,
			pars->l2_flag, pars->r_flag, pars->r2_flag, pars->dq_flag);
		printf("\n");
		pars = pars->next;
	}
}

void	lst_rev_print(t_new *pars)
{
	while (pars && pars->next != NULL)
		pars = pars->next;
	while (pars != NULL)
	{
		printf("<token: %s> <flag: %d> <d_flag: %d> ",
			pars->token, pars->flag, pars->d_flag);
		printf("\n");
		pars = pars->prev;
	}
}
// control - v then enter, gives ^M 