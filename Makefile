NAME	=		ls-render

CC		=		gcc -O3

WFLAGS	=		-Wall -Werror -Wextra

SRC		=		bresenham_line.c \
				check_line.c \
				help_functions.c \
				help_functions_for_draw_line.c \
				events1.c \
				events2.c \
				wu_line.c \
				input.c \
				fdf.c

SRC_DIR =		./src

OBJ		=		$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

OBJ_DIR	=		./obj

INC		=		-I ./include -I ./libft

LIBFT	=		-L ./libft -lft

MLX		=		-lmlx -framework OpenGL -framework AppKit

all: make_libs $(NAME)

$(NAME): $(OBJ)
	$(CC) $(WFLAGS) -I /usr/local/include $(OBJ) $(LIBFT) -L /usr/local/lib/ $(MLX) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(WFLAGS) $(INC) -o $@ -c $<

make_libs:
	@make -C ./libft

clean:
	/bin/rm -rf ./obj
	make -C ./libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
