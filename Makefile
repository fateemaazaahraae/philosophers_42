# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 20:21:03 by tiima             #+#    #+#              #
#    Updated: 2024/06/30 12:44:27 by fbazaz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread 
SRC = actions.c  main.c    parcing.c  routine.c  track.c init.c threads.c  utils.c get_set.c

OBJ = $(SRC:.c=.o)

all : $(NAME) 

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@clear

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all