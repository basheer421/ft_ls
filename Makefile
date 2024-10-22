# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 18:39:59 by bammar            #+#    #+#              #
#    Updated: 2024/10/22 16:35:04 by bammar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FILES_DIR = src

FILES = ft_ls.c parse.c parse_flags.c file_type.c \
	sort_files.c long_format.c get_max_len.c \
	get_files.c printing_utils.c rev.c

LIBFT_DIR = ./lib/libft

LIBFT = $(LIBFT_DIR)/libft.a

FILE_NAMES = $(addprefix $(FILES_DIR)/, $(FILES))

CC = cc	

CFLAGS = -Wall -Wextra -Werror -Ilib -std=c99

OBJS = $(FILE_NAMES:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re:	fclean all

.PHONY: all clean fclean re bonus
