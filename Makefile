# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 15:41:03 by nmartin           #+#    #+#              #
#    Updated: 2025/06/05 15:59:17 by nmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW = \033[33m
GREEN = \033[32m
PURPLE = \033[35m
BLUE = \033[34m
RESET = \033[0m

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -MMD -MP
MLXFLAGS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
NAME = cub3d
CUB_PATH = ./cub/
CUB_FILES = cub.c
CUB := $(addprefix $(CUB_PATH), $(CUB_FILES))
GAME_PATH = ./game/
GAME_FILES = game.c game_utils.c
GAME := $(addprefix $(GAME_PATH), $(GAME_FILES))
PARSING_PATH = ./parsing/
PARSING_FILES = parsing.c texture.c map.c map_utils.c free_map.c \
					check_map.c
PARSING := $(addprefix $(PARSING_PATH), $(PARSING_FILES))
MINIMAP_PATH = ./minimap/
MINIMAP_FILES = minimap.c
MINIMAP := $(addprefix $(MINIMAP_PATH), $(MINIMAP_FILES))
OBJ_PATH = ./objs/
OBJ := $(addprefix $(OBJ_PATH), $(CUB_FILES:.c=.o)) \
		$(addprefix $(OBJ_PATH), $(PARSING_FILES:.c=.o)) \
			$(addprefix $(OBJ_PATH), $(GAME_FILES:.c=.o)) \
				$(addprefix $(OBJ_PATH), $(MINIMAP_FILES:.c=.o))
SRC_BNS_PATH = ./srcs_bonus/
SRC_BNS_FILES = 
SRC_BNS := $(addprefix $(SRC_BNS_PATH), $(SRC_BNS_FILES))
OBJ_BNS := $(addprefix $(OBJ_PATH), $(SRC_BNS_FILES:.c=.o))
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
HEADERS = -Iheaders -I$(LIBFT_PATH)
DEPS := $(OBJ:.o=.d)

all : $(NAME)

bonus : all
#	@printf "$(BLUE)Creating $(NAME) bonus...$(RESET)"
#	@$(CC) $(CFLAGS) $(OBJ_BNS) $(LIBFT) -o $(NAME)
#	@printf "\r\033[K"
#	@printf "$(GREEN)$(NAME) created successfully\n$(RESET)"

$(NAME) : $(LIBFT) $(OBJ)
	@printf "$(PUPLE)Creating $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline $(MLXFLAGS)
	@printf "\r\033[K"
# 	@printf "$(GREEN)$(NAME) created successfully\n$(RESET)"
# 	@echo "$(PURPLE)▀█████████▄   ▄██████▄    ▄▄▄▄███▄▄▄▄   ▀█████████▄   ▄██████▄     ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█       $(RESET)"
# 	@echo "$(PURPLE)  ███    ███ ███    ███ ▄██▀▀▀███▀▀▀██▄   ███    ███ ███    ███   ███    ███   ███    ███     ███    ███ ███       ███       $(RESET)"
# 	@echo "$(PURPLE)  ███    ███ ███    ███ ███   ███   ███   ███    ███ ███    ███   ███    █▀    ███    ███     ███    █▀  ███       ███       $(RESET)"
# 	@echo "$(PURPLE) ▄███▄▄▄██▀  ███    ███ ███   ███   ███  ▄███▄▄▄██▀  ███    ███   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███       $(RESET)"
# 	@echo "$(PURPLE)▀▀███▀▀▀██▄  ███    ███ ███   ███   ███ ▀▀███▀▀▀██▄  ███    ███ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███       $(RESET)"
# 	@echo "$(PURPLE)  ███    ██▄ ███    ███ ███   ███   ███   ███    ██▄ ███    ███          ███   ███    ███     ███    █▄  ███       ███       $(RESET)"
# 	@echo "$(PURPLE)  ███    ███ ███    ███ ███   ███   ███   ███    ███ ███    ███    ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄ $(RESET)"
# 	@echo "$(PURPLE)▄█████████▀   ▀██████▀   ▀█   ███   █▀  ▄█████████▀   ▀██████▀   ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██ $(RESET)"
# 	@echo "$(PURPLE)                                                                                                         ▀         ▀         $(RESET)"

$(OBJ_PATH)%.o : $(CUB_PATH)%.c
	@printf "$(BLUE)Compiling $(NAME): [$<] $(RESET)"
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(OBJ_PATH)%.o : $(PARSING_PATH)%.c
	@printf "$(BLUE)Compiling $(NAME) parsing: [$<] $(RESET)"
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(OBJ_PATH)%.o : $(GAME_PATH)%.c
	@printf "$(BLUE)Compiling $(NAME) game: [$<] $(RESET)"
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(OBJ_PATH)%.o : $(MINIMAP_PATH)%.c
	@printf "$(BLUE)Compiling $(NAME) minimap: [$<] $(RESET)"
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(OBJ_BNS_PATH)%.o : $(SRC_BNS_PATH)%.c
	@printf "$(BLUE)Compiling $(NAME) bonus: [$<] $(RESET)"
	@mkdir -p $(OBJ_BNS_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "\r\033[K"

$(LIBFT) :
	@make -C $(LIBFT_PATH) --no-print-directory

clean :
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@rm -rf $(OBJ_PATH)
	@printf "$(YELLOW)Cleaned successfully\n$(RESET)"

fclean :
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@rm -rf $(OBJ_PATH)
	@rm -rf $(NAME)
	@printf "\r\033[K$(YELLOW)Full cleaned successfully\n$(RESET)"

re : fclean all


exec : fclean all
	@make clean --no-print-directory

.PHONY : all clean fclean re	

-include $(DEPS)
