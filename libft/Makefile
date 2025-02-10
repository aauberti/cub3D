NAME = libft.a

SRC = ft_isspace.c\
	ft_strcmp.c\
	ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_strlen.c\
	ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_strlcpy.c\
	ft_strlcat.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strncmp.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_strnstr.c\
	ft_atoi.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_strjoin.c\
	ft_split.c\
	ft_itoa.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_striteri.c\
	ft_putnbr_fd.c\
	ft_strmapi.c\
	ft_strtrim.c\
	ft_substr.c\
	get_next_line_bonus.c\
	ft_lstnew_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstsize_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstadd_back_bonus.c\
	ft_lstdelone_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstiter_bonus.c\
	ft_lstmap_bonus.c

OBJ_PATH = ./objects/

OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

CC = cc

CFLAGS = -Wall -Werror -Wextra -I.

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "\033[32mLibft compiled successfully\033[0m"

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "\033[34mObject files cleaned\033[0m"

fclean: clean 
	@rm -f $(NAME)
	@echo "\033[31mLibft.a removed\033[0m"

re : fclean all

.PHONY : clean fclean re all
