# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: claudialbombin                                 +#+  +:+       +#+     #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/19                               #+#    #+#              #
#    Updated: 2026/06/19                               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =  ft_atoi.c \
        ft_bzero.c \
        ft_calloc.c \
        ft_isalnum.c \
        ft_isalpha.c \
        ft_isascii.c \
        ft_isdigit.c \
        ft_isprint.c \
        ft_itoa.c \
        ft_lstadd_back.c \
        ft_lstadd_front.c \
        ft_lstclear.c \
        ft_lstdelone.c \
        ft_lstiter.c \
        ft_lstlast.c \
        ft_lstmap.c \
        ft_lstnew.c \
        ft_lstsize.c \
        ft_memchr.c \
        ft_memcmp.c \
        ft_memcpy.c \
        ft_memmove.c \
        ft_memset.c \
        ft_putchar_fd.c \
        ft_putendl_fd.c \
        ft_putnbr_fd.c \
        ft_putstr_fd.c \
        ft_split.c \
        ft_strchr.c \
        ft_strdup.c \
        ft_striteri.c \
        ft_strjoin.c \
        ft_strlcat.c \
        ft_strlcpy.c \
        ft_strlen.c \
        ft_strmapi.c \
        ft_strncmp.c \
        ft_strnstr.c \
        ft_strrchr.c \
        ft_strtrim.c \
        ft_substr.c \
        ft_tolower.c \
        ft_toupper.c


# Object files: substitutes .c with .o for each source file
OBJS = $(SRCS:.c=.o)

# Default target: builds the library
all: $(NAME)

# Builds the static library from object files
$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

# Removes object files only
clean:
	rm -f $(OBJS)

# Removes object files and the library (full clean)
fclean: clean
	rm -f $(NAME)

# Rebuilds everything: removes old files and compiles again
re: fclean all

# Marks these targets as not actual files (phony targets)
.PHONY: all clean fclean re
