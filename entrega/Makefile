# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/09 20:14:33 by abrecio-          #+#    #+#              #
#    Updated: 2025/06/14 13:04:58 by abrecio-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
PRINTF_DIR = ft_printf
PRINTF_BONUS_DIR = ft_printf_bonus

LIBFT = $(LIBFT_DIR)/libft.a

SRCS = $(PRINTF_DIR)/ft_printf_main.c \
       $(PRINTF_DIR)/ft_printf_utils.c

BONUS_SRCS = $(PRINTF_BONUS_DIR)/ft_printf_main_bonus.c \
             $(PRINTF_BONUS_DIR)/ft_printf_char_bonus.c \
             $(PRINTF_BONUS_DIR)/ft_printf_format_number_bonus.c \
             $(PRINTF_BONUS_DIR)/ft_printf_number_bonus.c \
             $(PRINTF_BONUS_DIR)/ft_printf_number_utils_bonus.c \
             $(PRINTF_BONUS_DIR)/ft_printf_parser_bonus.c \
             $(PRINTF_BONUS_DIR)/ft_printf_prefix_bonus.c \
             $(PRINTF_BONUS_DIR)/ft_printf_string_bonus.c \
             $(PRINTF_BONUS_DIR)/ft_printf_utils_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

INCLUDES = -I$(PRINTF_DIR) -I$(PRINTF_BONUS_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

bonus: $(LIBFT) $(BONUS_OBJS)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(BONUS_OBJS)
	touch bonus

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	rm -f bonus
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
