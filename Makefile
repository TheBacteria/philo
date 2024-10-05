# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzouine <mzouine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 11:58:20 by mzouine           #+#    #+#              #
#    Updated: 2024/10/05 13:51:04 by mzouine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c mz_utils.c mz_routine.c\
		mz_parser.c

SRC_BONUS = main.c\
			mz_parser.c

OBJS = ${SRC:.c=.o}
OBJS_BONUS = ${SRC_BONUS:.c=.o}
FLAGS = -g -pthread -Wall -Wextra -Werror #-fsanitize=thread
CC = cc
HEADER_BONUS = philo_bonus.h
HEADER = philo.h
RM = rm -f
NAME = philo
NAME_BONUS = philo_bonus

all: $(NAME)

%.o : %.c $(HEADER) $(HEADER_BONUS)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
		$(CC) $(FLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
		$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re