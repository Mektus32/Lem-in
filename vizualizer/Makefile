# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojessi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/11 17:20:05 by ojessi            #+#    #+#              #
#    Updated: 2019/07/15 21:15:09 by ojessi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = vizualizer

# src / obj files
SRC =   visu.c \
		read.c \
		draw.c \
		keyhook.c \
		dop_funct.c \
		funct_turn.c \
		funct_rooms.c \


OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

# compiler
CC = gcc
CFLAGS = -Wextra -Werror -Wall -g

# mlx library
MLX = ./minilibx/
MLX_LIB = $(addprefix $(MLX), mlx.a)
MLX_INC = -I ./minilibx
MLX_LNK = -L ./minilibx -l mlx -framework OpenGL -framework AppKit

FT = ../libft
FT_INC = -I ../libft
FT_LNK = -L ../libft -l ft

# directories
SRCDIR = ./src/
INCDIR = ./includes/
OBJDIR = ./obj/

all: $(NAME)

red:
	@echo "\x1B[31m"

grn:
	@echo "\x1B[32m"

off:
	@echo "\x1b[0m"

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(MLX_LIB):
	@make -C $(MLX)

$(NAME): obj $(MLX_LIB) grn $(OBJ)
	@$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)
	@echo "\x1b[0m"

clean: red
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
