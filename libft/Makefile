# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 18:41:50 by ayassin           #+#    #+#              #
#    Updated: 2022/08/24 10:40:44 by ayassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
	  ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c\
	  ft_memset.c ft_strchr.c ft_strncmp.c ft_strdup.c ft_strlcat.c ft_strlcpy.c\
	  ft_strlen.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_itoa.c\
	  ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c\
	  ft_striteri.c ft_strjoin.c ft_strlen.c ft_strmapi.c ft_strtrim.c\
	  ft_substr.c

BONUS = ft_lstadd_front.c ft_lstadd_back.c ft_lstclear.c ft_lstclear.c\
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c\
		ft_lstsize.c

CC = gcc

CFLAGS = -Werror -Wall -Wextra

OBJS = $(SRC:.c=.o)

BNSOBJS = $(BONUS:.c=.o)

all: bonus

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar cr $(NAME) $(OBJS)

bonus: $(BNSOBJS) $(OBJS)
	ar cr $(NAME) $(BNSOBJS) $(OBJS)

clean:
	rm -f $(OBJS)  $(BNSOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
