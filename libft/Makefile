# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojessi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/04 15:28:54 by ojessi            #+#    #+#              #
#    Updated: 2019/06/11 12:34:11 by ojessi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, obj, grn, off, red

NAME = libft.a
#src / obj files
SRC	=	ft_atoi.c \
		ft_bzero.c \
		ft_count_words.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_lstadd.c \
		ft_lstaddback.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putstr.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrev.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_setbackground_fd.c \
		ft_free_join.c \
		ft_list_add.c \
		ft_list_push_back.c \
		ft_list_foreach_if.c \
		ft_abs.c \
		ft_absf.c \
		ft_truncf.c \
		ft_pow.c \
		ft_free_strjoin_duo.c \
		ft_free_strjoin_rev.c \
		ft_ftoa.c \
		ft_ltoa_base.c \
		ft_ltoa.c \
		ft_ultoa_base.c \
		ft_ultoa.c \
		ft_frtwarr.c \
		get_next_line.c \
		ft_list_remove_free_if.c \
		ft_strtolower.c \
		ft_max.c \
		ft_min.c \
		ft_isdigonly.c

OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

#compiler
CC = gcc
CFLAGS = -Wextra -Wall -Werror -g

#directories
INCDIR = ./includes/
OBJDIR = ./obj/

all: obj grn $(NAME) off

red:
	@echo "\x1B[31m"

grn:
	@echo "\x1B[32m"

off:
	@echo "\x1b[0m"

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<

$(NAME): $(OBJ)	
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean: red
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME)
	
re: fclean all
