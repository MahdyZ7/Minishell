# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 08:40:39 by ayassin           #+#    #+#              #
#    Updated: 2022/08/24 10:47:28 by ayassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c $(EXECUTE_SRC_INDIR) $(EXECUTE_SRC_INDIR1)
 
EXECUTE_SRC = pipex.c pipex_utils.c  pipex_utils1.c pipex_utils2.c child.c \
				redirection.c redirection2.c here_doc.c signals.c \
				enviroment.c enviroment1.c enviroment2.c builtins.c builtins1.c
				
EXECUTE_SRC1 = p_assign_1.c p_assign_2.c p_dollar.c \
		p_expand.c p_list_assign.c p_list_normal.c big_list2.c \
		p_normal.c p_quote.c p_utils_1.c p_utils_2.c \
		prompt.c p_redirection.c big_list.c p_redirection2.c \
		p_expand1.c p_expand2.c p_expand3.c p_expand4.c  join_list.c\

EXECUTE_SRC_DIR = execute_src
				
EXECUTE_SRC_INDIR = $(addprefix $(EXECUTE_SRC_DIR)/,$(EXECUTE_SRC))

EXECUTE_SRC_DIR1 = parsing
				
EXECUTE_SRC_INDIR1 = $(addprefix $(EXECUTE_SRC_DIR1)/,$(EXECUTE_SRC1))

SUBDIRS = libft ft_printf

OBJS = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I/usr/local/opt/readline/include

all: $(NAME)

%.o : %.c
	@printf "\033[A\033[2K\r"
	$(CC) $(CFLAGS)  -Ilibft -Ift_printf -c $^ -o $@


$(NAME): $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFLAGS) $(SRC) -L/usr/local/opt/readline/lib -lreadline \
	-Lft_printf -lftprintf -Llibft -lft -o $(NAME)

clean:
	rm -f $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) clean -C $$dir; \
    done

fclean: clean
	rm -f $(NAME)
	for dir in $(SUBDIRS); do \
        $(MAKE) fclean -C $$dir; \
    done

re : fclean all

.PHONY: clean fclean all re