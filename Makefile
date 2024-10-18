# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 11:58:20 by mzouine           #+#    #+#              #
#    Updated: 2024/10/18 14:27:54 by mzouine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c mz_utils.c mz_routine.c mz_fail_handle.c mz_monitor.c mz_actions.c\
		mz_parser.c

OBJS = ${SRC:.c=.o}
FLAGS =  -Wall -Wextra -Werror #-g -fsanitize=thread
CC = cc
HEADER = philo.h
RM = rm -f
NAME = philo

all: $(NAME)

%.o : %.c $(HEADER) $(HEADER_BONUS)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re