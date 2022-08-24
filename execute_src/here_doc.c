/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:13:47 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/25 17:53:44 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// user input is regiterd for here doc
static char	*line_input(char *delimiter, char *line)
{
	char	*one_line;
	t_list	*node;

	one_line = NULL;
	if (ft_lstadd_backhelper(&g_m, line))
		return (NULL);
	node = ft_lstlast(g_m);
	while (1)
	{
		one_line = readline("> ");
		if (ft_strncmp_p(one_line, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		if (ft_strjoin_ms(&line, one_line) < 0 || ft_strjoin_ms(&line, "\n"))
		{
			free(one_line);
			free(line);
			return (NULL);
		}
		free(one_line);
		node->content = line;
	}
	free(one_line);
	if (line == NULL)
		line = ft_strdup("");
	return (line);
}

// child managing user input and sending it to parent
static void	line_input_child(char *delimiter, int *fd)
{
	char	*line;
	int		len;
	t_list	*node;

	line = NULL;
	node = ft_lstnew(fd);
	if (node == NULL)
		cleanexit(NULL, NULL, print_error("", "malloc failed", 1), fd);
	ft_lstadd_front(&g_m, node);
	close(fd[0]);
	line = line_input(delimiter, line);
	if (line == NULL)
		cleanexit(NULL, NULL, print_error("", "malloc failed", 1), fd);
	len = ft_strlen(line);
	write(fd[1], &len, sizeof(int));
	ft_putstr_fd(line, fd[1]);
	close(fd[1]);
	if (*line == '\0')
		free (line);
	cleanexit(NULL, NULL, 0, fd);
}

// parent waiting for child to send << input
static char	*line_input_parent(int id, int *fd)
{
	int		status;
	int		len;
	char	*line;

	status = 0;
	len = 0;
	line = NULL;
	waitpid(id, &status, 0);
	if (id == -1 || WEXITSTATUS(status))
	{
		close(fd[0]);
		close(fd[1]);
		free(fd);
		return (NULL);
	}
	close(fd[1]);
	read(fd[0], &len, sizeof(int));
	line = malloc(sizeof(char) * (len + 1));
	read(fd[0], line, len);
	close(fd[0]);
	line[len] = 0;
	free(fd);
	return (line);
}

// create a child for here doc
static char	*line_input_manager(char *delimiter)
{
	int		*fd;
	int		id;

	fd = (int *)malloc(sizeof(*fd) * 2);
	if (fd == NULL)
		return (NULL);
	if (pipe(fd) == -1)
		return (NULL);
	id = fork();
	if (id == 0)
		line_input_child(delimiter, fd);
	return (line_input_parent(id, fd));
}

// take input from << redirection
int	here_doc_input(t_new *lst)
{
	char	*delimiter;

	while (lst)
	{
		if (*(lst->token) == '<'
			&& *((lst->token) + 1) == '<' && lst->flag == 4)
		{
			if (*((lst->token) + 2) == '\0')
			{
				lst = lst->next;
				delimiter = lst->token;
				lst->token = line_input_manager(delimiter);
				if (lst->token == NULL)
					return (1);
				if (ft_lstadd_backhelper(&g_m, lst->token))
					cleanexit(NULL, NULL, 1, NULL);
			}
		}
		lst = lst->next;
	}
	return (0);
}
