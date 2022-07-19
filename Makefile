### OPERATING SYSTEM ###
OS= 		$(shell uname -s)

### EXECUTABLE ###
NAME=		fdf

### COMPILATION ###
CC=			gcc
CFLAGS=		-Wall -Werror -Wextra -g

### PATHS ###
LIBFT_PATH=	./libft/
INCL_PATH=	incl/
SRCS_PATH=	srcs/
OBJS_PATH=	objs/
ifeq ($(OS), Linux)
	MLX_PATH=	./mlx_linux/
else
	MLX_PATH=	./minilibx_macos/
endif

### SOURCE FILES ###
SRC_NAME=	$(NAME).c
SRC_BONUS=	$(NAME)_bonus.c
SRC_TESTS=	test1.c
SRCS=		utils.c \
			hooks.c \
			errors.c \
			read_map.c \
			draw_img.c \
			draw_map.c \
			menu.c
SRCS_NAME=	$(addprefix $(SRCS_PATH), $(SRC_NAME) $(SRCS))
SRCS_BONUS=	$(addprefix $(SRCS_PATH), $(SRC_BONUS) $(SRCS))
SRCS_TESTS=	$(addprefix $(SRCS_PATH), $(SRC_TESTS) $(SRCS))

### OBJECT FILES ### 
OBJ_NAME=	$(SRC_NAME:.c=.o)
OBJ_BONUS=	$(SRC_BONUS:.c=.o)
OBJ_TESTS=	$(SRC_TESTS:.c=.o)
OBJS=		$(SRCS:.c=.o)
OBJS_NAME=	$(addprefix $(OBJS_PATH), $(OBJ_NAME) $(OBJS))
OBJS_BONUS=	$(addprefix $(OBJS_PATH), $(OBJ_BONUS) $(OBJS))
OBJS_TESTS=	$(addprefix $(OBJS_PATH), $(OBJ_TESTS) $(OBJS))

### LIBFT ###
LIBFTMAKE=  make bonus --silent -C $(LIBFT_PATH)
LIBFT=      -L$(LIBFT_PATH) -lft

### MLXLIB ###
MLXMAKE=	make --silent -C $(MLX_PATH)
ifeq ($(OS), Linux)
	MLX=	-L$(MLX_PATH) -lmlx_Linux -lX11 -lXext -lm -lz -O3
else
	MLX=	-L$(MLX_PATH) -lmlx -lm -framework OpenGL -framework AppKit -O3
endif

### INCLUDES ###
INC=		-I $(LIBFT_PATH)$(INCL_PATH) -I $(INCL_PATH) -I $(MLX_PATH)

### COLOURS ###
GREEN= \033[1;32m
RED= \033[1;31m
DEFAULT= \033[0m

### IMPLICT RULES ###
$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

### ACTIVE RULES ###
all: $(NAME)

$(NAME): $(OBJS_PATH) $(OBJS_NAME)
	@$(LIBFTMAKE)
	@$(MLXMAKE)
	@$(CC) $(CFLAGS) $(OBJS_NAME) $(INC) $(LIBFT) $(MLX) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) Program created$(DEFAULT)"

bonus: $(OBJS_PATH) $(OBJS_BONUS)
	@$(LIBFTMAKE)
	@$(MLXMAKE)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(INC) $(LIBFT) $(MLX) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) Program created$(DEFAULT)"

test: $(OBJS_PATH) $(OBJS_TESTS)
	@$(LIBFTMAKE)
	@$(MLXMAKE)
	@$(CC) $(CFLAGS) $(OBJS_TESTS) $(INC) $(LIBFT) $(MLX) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) Program created$(DEFAULT)"

$(OBJS_PATH):
	@mkdir -p $@
	
clean:
	@make $@ --silent -C $(LIBFT_PATH)
	@rm -rf $(OBJS_PATH)
	@echo -e "$(RED)Object files removed$(DEFAULT)"

fclean: clean
	@make $@ --silent -C $(LIBFT_PATH)
	@echo -e "$(RED)Libft removed$(DEFAULT)"
	@rm -f $(NAME)
	@echo -e "$(RED)$(NAME) Program removed$(DEFAULT)"

re: fclean all

### NORMINETTE ###
norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS_PATH)
	@norminette -R CheckForbiddenSourceHeader $(INCL_PATH)
	@norminette -R CheckDefine $(SRCS_PATH)
	@norminette -R CheckDefine $(INCL_PATH)

### PHONY RULE ###
.PHONY:	all bonus clean fclean re norm
