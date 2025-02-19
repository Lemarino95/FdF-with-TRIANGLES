CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = fdf
OBJ_DIR = obj

SRC_MAIN = fdf_readmap.c fdf_main.c fdf_drawline.c


OBJECTS_MAIN = $(SRC_MAIN:%.c=$(OBJ_DIR)/%.o)
OBJECTS = $(OBJECTS_MAIN)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR =  minilibx-linux
MINILIBX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lm -lX11 -lXext


all: $(NAME)
	@echo "Object files created!"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(MLX_DIR):
#	scarica archivio(.tgz)
	@curl https://cdn.intra.42.fr/document/document/26198/$(MLX_DIR).tgz --output $(MLX_DIR).tgz
#	tar = estrarre archivio
	@tar -xf $(MLX_DIR).tgz
	@rm $(MLX_DIR).tgz

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(MINILIBX): $(MLX_DIR)
	@$(MAKE) -C $(MLX_DIR) --quiet

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MINILIBX) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@	${CC} -c ${CFLAGS} -I. -I$(LIBFT_DIR) -I$(MLX_DIR) $< -o $@

clean:
	@echo "Cleaning..."
	@	rm -rf $(OBJECTS) $(OBJ_DIR)
	@	$(MAKE) -C $(LIBFT_DIR) clean --quiet

fclean: clean
	@echo "Full Cleaning..."
	@	rm -rf $(OBJ_DIR) $(NAME)
	@	$(MAKE) -C $(LIBFT_DIR) fclean --quiet

re: fclean all

libft: $(LIBFT)
minilibx: $(MINILIBX)

.PHONY: all clean fclean re libft minilibx
