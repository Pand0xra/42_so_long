CC= cc
CFLAGS= -Wall -Wextra -Werror -g
NAME= so_long
SRCS		= $(wildcard srcs/*.c)
OBJS		= $(SRCS:.c=.o)
RM			= rm -rf

SRCS_BONUS	= $(wildcard srcs_bonus/*.c)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a
LIBS		= -L $(LIBFT_PATH) -lft

MLX_PATH	= ./minilibx-linux
MLX			= $(MLX_PATH)/libmlx.a
MLXS		= -L minilibx-linux -lmlx -lXext -lX11 -lm -lz

VAL 		= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

RESET		= \033[0m
GREEN		= \033[32;01m
BLUE		= \033[34;01m
RED			= \033[31;01m
YELLOW		= \033[0;93m
CYAN		= \033[0;96m

.PHONY: 	all clean fclean re rebonus bonus run

all: 		$(NAME)

$(LIBFT): 	./libft/*.c
			@echo "$(BLUE)----Compiling lib----$(RESET)"
			@$(MAKE) -C $(LIBFT_PATH) > /dev/null 2>&1
			@echo "$(GREEN)libft ready!$(RESET)"

$(MLX): 	./minilibx-linux/*.c
			@echo "$(BLUE)----Compiling minilibx----$(RESET)"
			@$(MAKE) -C $(MLX_PATH) > /dev/null 2>&1
			@echo "$(GREEN)minilibx ready!$(RESET)"
	
$(NAME): 	$(OBJS) $(LIBFT) $(MLX)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS) $(MLXS)
			@echo "\033[33mso_long Compiled! \033[31mᕦ(♥\033[32m_\033[31m♥\033[32m)ᕤ"

%.o: 		%.c
			@$(CC) $(CFLAGS) -c $< -o $@
clean:
			@$(RM) $(OBJS) $(OBJS_BONUS) > /dev/null 2>&1
			@$(MAKE) clean -C $(LIBFT_PATH) > /dev/null 2>&1
			@$(MAKE) clean -C $(MLX_PATH) > /dev/null 2>&1
			@echo "$(CYAN)Cleaned all .o files.$(RESET)"

fclean: 	clean
			@$(MAKE) clean -C $(LIBFT_PATH) > /dev/null 2>&1
			@$(MAKE) clean -C $(MLX_PATH) > /dev/null 2>&1
			@$(RM) $(NAME)
			@echo "$(CYAN)Cleaned $(NAME), libft and minilibx.$(RESET)"

bonus: 		clean $(OBJS_BONUS) $(LIBFT) $(MLX)
			@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME) $(LIBS) $(MLXS) > /dev/null 2>&1
			@echo "\033[33mso_long Bonus Compiled! \033[31mᕦ(♥\033[32m_\033[31m♥\033[32m)ᕤ"

run:		$(NAME)
			./$(NAME) assets/maps/valid/map4.ber

re: 		fclean all

rebonus:	fclean bonus
