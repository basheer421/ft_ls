# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 18:39:59 by bammar            #+#    #+#              #
#    Updated: 2024/07/01 17:59:27 by bammar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_ltoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
	ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
	ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
	ft_substr.c ft_tolower.c ft_toupper.c ft_strcmp.c ft_malloc.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
	ft_lstiter.c ft_lstmap.c

HT = ht_clear.c     ht_destroy.c  ht_isempty.c  ht_remove.c   ht_set.c \
	ht_contains.c  ht_get.c      ht_hash.c  ht_new.c      ht_replace.c

FILES += $(addprefix hashtable/, $(HT))
	
DQ = ft_dlstnew.c  ft_dqadd_first.c  ft_dqcontains.c   ft_dqdel_last.c  ft_dqsize.c \
	ft_dqadd_last.c   ft_dqdel_first.c  ft_dqnew.c ft_dqdel.c

FILES += $(addprefix ft_deque/, $(DQ))

PF = ft_printf.c ft_printf_utils.c

FILES += $(addprefix ft_printf/, $(PF))

CC = cc	

CFLAGS = -Wall -Wextra -Werror

OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS) 

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re bonus
