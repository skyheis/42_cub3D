# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 17:49:20 by ggiannit          #+#    #+#              #
#    Updated: 2023/05/05 23:38:38 by ggiannit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####### NAME #########

NAME = cub3D
BNUS = bonus

###### VARIABLE ######

INCLUDE = include
MLX_PATH = minilibx

DIRSRCS =
DIROBJS = obj/

FLSRCS = main.c dda.c engine.c engine_utils.c key_hooks.c wall_line.c \
		 map.c check_map.c check_player.c map_split.c map_utils.c \
		 handle_error.c minimap.c

FLOBJS = ${FLSRCS:.c=.o}

OBJS = $(addprefix $(DIROBJS),$(FLOBJS))

ARUSD = libft.a libmlx.a
ARUSDDIR = archive/

ARINC = $(addprefix $(ARUSDDIR),$(ARUSD))

CC = gcc
#CC = clang
AR = ar
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -lm -lX11 -lXext #-lmlx

######## EXT #########

# make a .o file using a .c file
# $< for the .c file
# $@ for the .o file

# .inextention.outextention:

#.c.o:
$(DIROBJS)%.o: $(DIRSRCS)%.c
	@echo "$(GREEN)Compiling:$(BLUE) $< $(DEF_COLOR)"
	@${CC} ${CFLAGS} -I ${INCLUDE} -c $< -o $@

####### RULES ########

all: minilibx libft ${NAME}

${NAME}: ${OBJS}
	@echo "$(YELLOW)- Program Name: $(WHITE)${NAME}$(DEF_COLOR)"
	@echo "$(YELLOW)- Compiler: $(WHITE)${CC}$(DEF_COLOR)"
	@echo "$(YELLOW)- Flags: $(WHITE)${CFLAGS}$(DEF_COLOR)"
	@${CC} ${CFLAGS} -L $(ARUSDDIR) -I $(INCLUDE) -o $(NAME) $(OBJS) $(ARINC) $(MLXFLAGS) 

clean:
	@make -sC minilibx clean
	@make -sC libft clean
	@${RM} ${OBJS} 
	@echo "$(RED)All $(CYAN)$(NAME)$(RED)'s objects removed with $(WHITE)${RM}$(DEF_COLOR) 🧹" 

fclean: clean
	@${RM} ${PRNAME} archive/libft.a archive/libmlx.a
	@echo "$(RED)..and $(CYAN)${NAME} $(RED)as been removed$(DEF_COLOR) 🚮"

libft:
	@make -sC libft

libftclean:
	@make -sC libft clean

libftfclean:
	@make -sC libft fclean

re: fclean all

minilibx:
	@make -sC $(MLX_PATH)
	@cp $(MLX_PATH)/mlx.h $(INCLUDE)/mlx.h
	@cp $(MLX_PATH)/libmlx_Linux.a $(ARUSDDIR)/libmlx.a

.PHONY: all clean fclean re starting .c.o libft libftclean libftfclean minilibx
.SUFFIXES: .c .o 

###### COLORS ########

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#####################
