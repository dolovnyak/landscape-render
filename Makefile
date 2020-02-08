NAME		=		ls-render

CC		=		gcc -O3

WFLAGS		=		-Wall -Werror -Wextra

SRC		=		bresenham_line.c \
				check_line.c \
				help_functions.c \
				help_functions_for_draw_line.c \
				events1.c \
				events2.c \
				wu_line.c \
				input.c \
				fdf.c

SRC_DIR		=		./src

OBJ		=		$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

OBJ_DIR		=		./obj

INC		=		-I ./include -I ./libft -I ./minilibx_macos

LIBFT		=		-L ./libft -lft

MLX		=		-L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit

all: make_libs $(NAME)

$(NAME): $(OBJ)
	$(CC) $(WFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(WFLAGS) $(INC) -o $@ -c $<

make_libs:
	@make -C ./libft
	@make -C ./minilibx_macos

clean:
	/bin/rm -rf ./obj
	make -C ./libft/ clean
	make -C ./minilibx_macos/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft/ fclean
	make -C ./minilibx_macos/ clean

re: fclean all
