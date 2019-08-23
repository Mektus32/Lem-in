# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojessi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/30 16:17:00 by ojessi            #+#    #+#              #
#    Updated: 2019/08/23 11:08:59 by ojessi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, obj, red, grn, off, vis

NAME = lem-in

# src / obj files
SRC =	bfs.c \
		main.c \
 		liba.c \
 		liba_2.c \
 		free.c \
 		path.c \
 		valid.c \
 		ft_bfs_k.c \
 		ant_room.c \
 		list_path.c \
 		list_room.c \
 		suurballe.c \
 		ft_list_i.c \
 		valid_link.c \
 		ft_list_i_2.c \
 		ft_list_down.c \
 		check_n_path.c \
 		ant_in_room_2.c \
 		ft_list_down_2.c \


OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

# compiler
CC = gcc
CFLAGS = -Wextra -Wall -Werror

# ft library
FT = ./libft
FT_LIB = $(addprefix $(FT), libft.a)
FT_INC = -I ./libft
FT_LNK = ./libft/libft.a

# printf library
PR = ./ft_printf
PR_LIB = $(addprefix $(PR), libftprintf.a)
PR_INC = -I ./ft_printf
PR_LNK = ./ft_printf/libftprintf.a

# visual
VI = ./vizualizer

# directories
SRCDIR = ./src/
INCDIR = -I ./includes/
OBJDIR = ./obj/

all: $(NAME)

$(NAME): obj $(FT_LIB) $(PR_LIB) grn $(OBJ) vis
	@$(CC) $(CFLAGS) $(OBJ) $(PR_LNK) $(FT_LNK) -lm -o $(NAME)
	@echo "\x1b[0m"

red:
	@echo "\x1B[31m"

grn:
	@echo "\x1B[32m"

off:
	@echo "\x1b[0m"

obj:
	@mkdir -p $(OBJDIR)

$(FT_LIB):
	@make -C $(FT)

$(PR_LIB):
	@make -C $(PR)

vis:
	@make -C $(VI)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(PR_INC) $(FT_INC) $(INCDIR) -o $@ -c $<

clean: red
	/bin/rm -rf $(OBJDIR)
	@make -C $(FT) clean
	@make -C $(PR) clean
	@make -C $(VI) clean

fclean: clean
	/bin/rm -rf $(NAME)
	make -C $(FT) fclean
	make -C $(PR) fclean
	make -C $(VI) fclean

re: fclean all
