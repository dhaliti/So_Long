# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 01:08:17 by dhaliti           #+#    #+#              #
#    Updated: 2022/03/16 10:41:16 by dhaliti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m
SRCS		= 	srcs/main.c \
				srcs/build_map.c \
				srcs/check_map.c \
				srcs/pokemon.c \
				srcs/movements.c \
				srcs/utils.c
NAME		= pokemon
OBJS_DIR	= objs/
PROJECT_H	= srcs/pokemon.h
OBJS		= $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
CC			= gcc
CC_FLAGS	= -Wall -Werror -Wextra
MLXFLAGS = -framework OpenGL -framework AppKit

$(OBJS_DIR)%.o : %.c $(PROJECT_H)
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD]${RST} '$<' $(END)"

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS) ./LIBFT/libft.a ./MINILIBX/libmlx.a ${MLXFLAGS}
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

all: $(NAME)

maker:
	@make -C ./LIBFT
	@make -C ./MINILIBX

clean:
	@make clean -C ./LIBFT
	@make clean -C ./MINILIBX
	@rm -rf $(OBJS_DIR)
	@printf "\033[2K\r${GRN}[CLEAN]${RST} done$(END)"

fclean: clean
	@make fclean -C ./LIBFT
#	@make fclean -C ./MINILIBX
	@rm -f $(NAME)
	@printf "\033[2K\r${GRN}[FCLEAN]${RST} done$(END)"

re: fclean all

.PHONY:		all clean fclean re
