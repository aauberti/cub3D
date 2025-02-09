NAME	= cub3D

CC		= clang
CFLAGS	= -Werror -Wextra -Wall -g

SRC_PATH = ./sources/
OBJ_PATH = ./objects/
INC_PATH = ./includes/

SRC		= 	main.c \
			NAME	= cub3D

CC		= clang
CFLAGS	= -Werror -Wextra -Wall -g

SRC_PATH = ./sources/
OBJ_PATH = ./objects/
INC_PATH = ./includes/

SRC		= 	main.c \
			NAME	= cub3D

CC		= clang
CFLAGS	= -Werror -Wextra -Wall -g

SRC_PATH = ./sources/
OBJ_PATH = ./objects/
INC_PATH = ./includes/

SRC		= 	main.c \
			parsing/check_map.c\
			

OBJS	= $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

all: $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(LIBFT) $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) -lreadline
	@echo "\033[32m$(NAME) created!\033[0m"

$(LIBFT):
	@echo "Making libft..."
	@make -C $(LIBFT_PATH)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all re clean fclean