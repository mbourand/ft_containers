# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/14 15:50:28 by mbourand          #+#    #+#              #
#    Updated: 2020/09/09 14:53:30 by mbourand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_containers
CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -std=c++98
SRC_PATH= srcs/
OBJ_PATH= objs/

SRC_NAME=	TestList.cpp TestMap.cpp TestQueue.cpp \
			TestStack.cpp TestVector.cpp main.cpp Utils.cpp

OBJ_NAME= $(SRC_NAME:.cpp=.o)

INC= -I incs/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
DEF= \033[0m
RED= \033[31;1m
GRN= \033[32;1m
YEL= \033[33;1m

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(RED)[ft_containers] : $(DEF)Compiling..."
	@$(CC) $(CFLAGS) -fsanitize=address -g3 -o $(NAME) $(OBJ) $(INC)
	@echo "$(RED)[ft_containers] : $(DEF)Compilation $(GRN)[OK]$(DEF)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@echo "$(RED)[ft_containers] :$(DEF) Compiling $@"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(RED)[ft_containers] : $(DEF)Cleaning $(GRN)[OK]$(DEF)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)[ft_containers] : $(DEF)Full Cleaning $(GRN)[OK]$(DEF)"

re: fclean all
