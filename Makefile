# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/15 22:24:05 by thhusser          #+#    #+#              #
#    Updated: 2022/04/13 14:55:45 by thhusser         ###   ########.fr        #
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
		  		utils.c key_events.c \
		 		player.c texture.c grid.c \
				images.c \
				window.c utils_init.c \
				utils_render.c \
				error.c \
				parsers/parse_input.c \
				parsers/map/check_borders.c \
				parsers/map/check_walls.c \
				parsers/map/parse_map.c \
				parsers/map/parse_map2.c \
				parsers/parameters/parse_line_paths.c \
				parsers/parameters/check_open_file.c \
				utils/append_error.c \
				utils/detect_line_map.c \
				utils/ft_is_number.c \
				utils/is_in_charset.c \
				utils/number_of_args.c \
				list_map.c \
				utils/preli.c \
	
SRCS_BONUS	= $(addprefix ./srcs_bonus/, ${SRCS_FILES_BONUS})
SRCS_FILES_BONUS		= \
				main_bonus.c \
				render_bonus.c \
				cast_hz_bonus.c \
				cast_vt_bonus.c \
				cast_ray_bonus.c \
				utils_bonus.c \
				key_events_bonus.c \
				player_bonus.c \
				texture_bonus.c \
				grid_bonus.c  \
				images_bonus.c  \
				window_bonus.c \
				window.c_bonus.c  \
				utils_render_bonus.c \
				error_bonus.c \
				parsers/parse_input_bonus.c \
				parsers/map/check_borders_bonus.c  \
				parsers/map/check_walls_bonus.c  \
				parsers/map/parse_map_bonus.c \
				parsers/map/parse_map2_bonus.c \
				parsers/parameters/parse_line_paths_bonus.c \
				parsers/parameters/check_open_file_bonus.c \
				utils/append_error_bonus.c \
				utils/detect_line_map_bonus.c \
				utils/ft_is_number_bonus.c \
				utils/is_in_charset_bonus.c  \
				utils/number_of_args_bonus.c  \
				list_map_bonus.c  \
				utils/preli_bonus.c \
				render_2d_bonus.c \

CC			=	clang

FLAGS		= 	-Werror -Wextra -Wall

PATH_LIBFT 	= ./libft/

PATH_MLX 	= ./minilibx/

HEADER		= -I ./includes

OBJS		= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

RM 			= rm -f

.c.o:
				@printf "$(_WHITE)Generating $(NAME) objects... %-33.33s\r$(_NC)" $@
				@clang ${FLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all:		${NAME}

$(NAME): 	${OBJS}
			@make -C libft/
			@echo ""
			@$(CC) $(FLAGS) $(HEADER) $(OBJS) -o $(NAME) -L ${PATH_LIBFT} -lft -L ${PATH_MLX} -lmlx -lXext -lX11 -lm
			@echo "$(_GREEN)Generating $(NAME)$(_NC)"

bonus: 		${OBJS_BONUS}
			@make -C libft/
			@echo ""
			@$(CC) $(FLAGS) $(HEADER) $(OBJS_BONUS) -o $(NAME)_bonus -L ${PATH_LIBFT} -lft -L ${PATH_MLX} -lmlx -lXext -lX11 -lm -g
			@echo "$(_GREEN)Generating $(NAME)_bonus$(_NC)"

clean:
			@make clean -C ./libft
ifneq ($(wildcard $(OBJS)),)
	@$(RM) $(OBJS)
	@echo "$(_GREEN)Delete objects files $(NAME)$(_NC)"
endif
ifneq ($(wildcard $(OBJS_BONUS)),)
	@$(RM) $(OBJS_BONUS)
	@echo "$(_GREEN)Delete objects files $(NAME)_bonus$(_NC)"
endif

fclean:		clean
			@make fclean -C ./libft
ifneq ($(wildcard $(NAME)),)
	@$(RM) $(NAME)
	@echo "$(_GREEN)Delete $(NAME)$(_NC)"
endif
ifneq ($(wildcard $(NAME)_bonus),)
	@$(RM) $(NAME)_bonus
	@echo "$(_GREEN)Delete $(NAME)_bonus$(_NC)"
endif

re:			fclean all

.PHONY: 	all fclean clean re

