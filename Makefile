NAME	= cub3D

MFLAGS = --no-print-directory
CC		= cc
CFLAGS	= -Werror -Wextra -Wall -g

SRC_PATH = ./sources/
OBJ_PATH = ./objects/
INC_PATH = ./includes/

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

SRC		= 	main.c \
			parsing/check_param.c \
			parsing/init_data.c \
			parsing/valid_path.c \
			parsing/valid_color.c \
			parsing/parse_elem.c \
			free_data.c \
			
			

OBJS	= $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH) -I $(MLX_DIR)


all: $(LIBFT) $(MLX_LIB) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(LIBFT) $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) -lXext -lX11 -lm -o $@ $(INC) $(LIBFT) 
	@echo "\033[32m$(NAME) created!\033[0m"

$(LIBFT):
	@echo "Making libft..."
	@make $(MFLAGS) -C $(LIBFT_PATH)

$(MLX_LIB):
	@echo "Making minilibx..."
	@make $(MFLAGS) -C $(MLX_DIR)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_PATH)
	@make $(MFLAGS) -C $(LIBFT_PATH) clean
	@if [ -d $(MLX_DIR) ]; then make $(MFLAGS) -C $(MLX_DIR) clean; fi

fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME)
	@make $(MFLAGS) -C $(LIBFT_PATH) fclean
	@if [ -d $(MLX_DIR) ]; then make $(MFLAGS) -C $(MLX_DIR) clean; fi

re: fclean all

.PHONY: all re clean fclean