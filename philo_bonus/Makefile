# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 11:58:20 by mzouine           #+#    #+#              #
#    Updated: 2024/10/18 15:27:31 by mzouine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main_bonus.c mz_utils_bonus.c mz_routine_bonus.c mz_fail_handle_bonus.c\
		mz_monitor_bonus.c mz_actions_bonus.c mz_parser_bonus.c

OBJS = ${SRC:.c=.o}
FLAGS =  -Wall -Wextra -Werror
CC = cc
HEADER = philo_bonus.h
RM = rm -f
NAME = philo_bonus

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