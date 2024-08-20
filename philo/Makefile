# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/23 18:00:27 by pgonzal2          #+#    #+#              #
#    Updated: 2024/08/20 17:20:06 by pgonzal2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread
NAME = philo
SRCS = main.c \
		utils.c \
		routine.c \
		monitor.c \
		init_struct.c \
		utils_two.c \
		

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	
fclean: clean
		rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re