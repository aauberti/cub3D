NAME		= cub3D
MFLAGS 		= --no-print-directory
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

# Directories
SRC_DIR		= ./src
OBJ_DIR		= ./obj
INC_DIR		= ./includes
LIBFT_DIR	= ./libft
MLX_DIR		= ./minilibx-linux

# Source files
SRC		= 	main.c \
			hooks.c \
			memory.c \
			render.c \
			movement.c \
			parsing/check_cell.c \
			parsing/init_data.c \
			parsing/parse_elem.c \
			parsing/parse_map.c \
			parsing/parsing_utils.c \
			parsing/check_param.c \
			parsing/valid_path.c \
			parsing/valid_color.c \
			parsing/free_data.c \
			render/draw.c \
			render/draw_utils.c \
			render/dda.c \
			render/texture.c \
			render/vertical_line.c

OBJS	= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
INC		= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS	= $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a

# Libraries flags
MLX_FLAGS	= -lX11 -lXext -lm

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	@echo "Making libft..."
	@make $(MFLAGS) -C $(LIBFT_DIR)
	@echo "Making minilibx..."
	@make $(MFLAGS) -C $(MLX_DIR)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS) $(MLX_FLAGS)
	@echo "\033[32m$(NAME) created!\033[0m"

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@make $(MFLAGS) -C $(LIBFT_DIR) clean
	@if [ -d $(MLX_DIR) ]; then make $(MFLAGS) -C $(MLX_DIR) clean; fi

fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME)
	@make $(MFLAGS) -C $(LIBFT_DIR) fclean
	@if [ -d $(MLX_DIR) ]; then make $(MFLAGS) -C $(MLX_DIR) clean; fi

re: fclean all

.PHONY: all clean fclean re