# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/15 22:24:05 by thhusser          #+#    #+#              #
#    Updated: 2021/12/01 17:39:12 by thhusser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_NC=`tput sgr0`
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_BLUE=\033[0;34m
_PURPLE=\033[0;95m
_CYAN=\033[0;36m
_WHITE=\033[0;37m

NAME		= cub3D

SRCS		= $(addprefix ./srcs/, ${SRCS_FILES})

SRCS_FILES	= \
				main.c \
				render.c cast_hz.c cast_vt.c cast_ray.c \
		  		utils.c key_events.c parsing.c \
		 		player.c texture.c grid.c utils_parsing.c \
				grid_parsing.c colors.c resolution.c images.c \
				window.c utils_init.c sprites.c \
				utils_sprites.c utils_render.c render_sprites.c \
				utils_colors.c error.c \
				parsers/map/check_border.c \
				parsers/map/check_walls.c \
				parsers/map/parse_map.c \
				parsers/parameters/parse_line_paths.c \
				utils/append_error.c \
				utils/detect_line_map.c \
				utils/dual_realloc.c \
				utils/ft_is_number.c \
				utils/is_in_charset.c \
				utils/number_of_args.c \
				

CC			=	clang

FLAGS		= 	-Werror -Wextra -Wall -g

PATH_LIBFT 	= ./libft/

PATH_MLX 	= ./minilibx/

HEADER		= -I ./includes

OBJS		= ${SRCS:.c=.o}

RM 			= rm -f

.c.o:
				@printf "$(_WHITE)Generating philo objects... %-33.33s\r$(_NC)" $@
				@clang ${FLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all:		${NAME}

$(NAME): 	${OBJS}
			@make -C libft/
			@echo ""
			@$(CC) $(FLAGS) -g $(HEADER) $(OBJS) -o $(NAME) -L ${PATH_LIBFT} -lft -L ${PATH_MLX} -lmlx -lXext -lX11 -lm
			@echo "$(_GREEN)Generating $(NAME)$(_NC)"

exec:		${NAME}
			@clear
			@echo "Creating and executing ./$(NAME)"
			@echo "#####################################"
			@./${NAME} assets/small_map.cub

# execv:		${NAME}
#			@$(CC) $(FLAGS) -g $(HEADER) $(OBJS) -o $(NAME) -L ${PATH_LIBFT} -lft -L ${PATH_MLX} -lmlx -lXext -lX11 -lm
# 			@echo "Creating and executing ./cub3D"
# 			@echo "#####################################"
# 			@echo "# SANITIZING [LLDB].................#"
# 			@echo "#####################################"
# 			@~/.local/bin/colour-valgrind -v --show-leak-kinds=all --tool=memcheck --leak-check=full  --track-origins=yes ./${NAME} assets/map.cub
# # 			valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes ./${NAME} assets/small_map.cub

# execf:		${NAME}
# 			@$(CC) -g -fsanitize=address $(FLAGS) $(HEADER) $(OBJS) -o $(NAME) -L ${PATH_LIBFT} -lft -L ${PATH_MLX} -lmlx -lXext -lX11 -lm
# 			@echo "Creating and executing ./cub3D"
# 			@echo "#####################################"
# 			@echo "# SANITIZING [FSANITIZE ADDRESS]....#"
# 			@echo "#####################################"
# 			@./${NAME} assets/small_map.cub

clean:
			@make clean -C ./libft
ifneq ($(wildcard $(OBJS)),)
	@$(RM) $(OBJS)
	@echo "$(_GREEN)Deletes objects files $(NAME)$(_NC)"
endif

fclean:		clean
			@make fclean -C ./libft
ifneq ($(wildcard $(NAME)),)
	@$(RM) $(NAME)
	@echo "$(_GREEN)Delete $(NAME)$(_NC)"
endif

re:			fclean all

.PHONY: 	all fclean clean re

