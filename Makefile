# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/15 22:24:05 by thhusser          #+#    #+#              #
#    Updated: 2021/11/29 17:39:51 by thhusser         ###   ########.fr        #
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
				parsers/parse_input.c \
				parsers/map/parse_map.c \
				parsers/map/check_borders.c \
				parsers/map/check_walls.c \
				parsers/parameters/parse_line_resolution.c \
				parsers/parameters/parse_line_paths.c \
				utils/is_in_charset.c \
				utils/ft_is_number.c \
				utils/number_of_args.c \
				utils/dual_realloc.c \
				utils/detect_line_map.c \
				utils/append_error.c \
				utils/show_errors.c \
				init/init_global_struct.c \
				free/free_everything.c \
				free/free_mlx.c \
				list_map.c \
				images.c \
				window.c \
				textures.c \
				key_event.c \
				print_data/print.c \
				player.c \
				print_pxl.c \
				error.c
				


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
			@echo "Creating and executing ./cub3D"
			@echo "#####################################"
#			@./${NAME} assets/small_map.cub

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

