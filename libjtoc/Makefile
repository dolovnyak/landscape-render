# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/07 16:14:32 by sbednar           #+#    #+#              #
#    Updated: 2019/08/19 03:07:45 by sbecker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	libjtoc.a

SRC_DIR		=	./src
OBJ_DIR		=	./obj
INC_DIR		=	./include

FT_DIR		=	../libft
FT_INC_DIR	=	../libft/include

SRC			=	jtoc_read_file.c \
				jtoc_validate.c \
				jtoc_validate_value.c \
				jtoc_parse.c \
				jtoc_parse_value.c \
				jtoc_parse_number.c \
				jtoc_utils.c \
				jtoc_utils2.c \
				jtoc_node.c \
				jtoc_read.c \
				jtoc_get.c

OBJ			=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

INCS		=	-I$(INC_DIR) -I$(FT_INC_DIR)
LIBS		=	-L$(FT_DIR) -lft

CC 			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -O3

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
