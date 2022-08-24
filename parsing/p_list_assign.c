/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_list_assign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:34:28 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/08/06 12:52:45 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_add_newvar(t_var **var, char *line)
{
	t_list	*tmp;

	(*var) = malloc(sizeof(t_var));
	tmp = ft_lstnew((void *)(*var));
	ft_lstadd_back(&g_m, tmp);
	(*var)->key = get_key(line);
	while (*line != '=' && *line)
		line++;
	line++;
	(*var)->value = get_value(line);
	(*var)->prev = NULL;
	(*var)->next = NULL;
}

void	lst_add_backvar(t_var **var, char *line)
{
	t_var	*tem;
	t_var	*t;
	t_list	*tmp;

	tem = *var;
	t = malloc(sizeof(t_var));
	tmp = ft_lstnew((void *)(t));
	ft_lstadd_back(&g_m, tmp);
	while ((*var)->next)
		*var = (*var)->next;
	t->key = get_key(line);
	while (*line != '=' && *line)
		line++;
	line++;
	t->value = get_value(line);
	(*var)->next = t;
	t->prev = *var;
	*var = tem;
}

void	lst_print_vars(t_var *vars)
{
	while (vars != NULL)
	{
		printf("<key: %s> <value: %s> \n", vars->key, vars->value);
		vars = vars->next;
	}
}
