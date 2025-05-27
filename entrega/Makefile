# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abrecio- <abrecio-@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 00:17:05 by abrecio-          #+#    #+#              #
#    Updated: 2025/05/26 00:18:00 by abrecio-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = clang
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft.a

SRCS = ft_printf_main.c \
       ft_printf_char.c \
       ft_printf_charstr.c \
       ft_printf_format.c \
       ft_printf_number.c \
       ft_printf_number_utils.c \
       ft_printf_parser.c \
       ft_printf_prefix.c \
       ft_printf_string.c \
       ft_printf_pointer.c \
       ft_printf_utils.c

OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m 

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Creando librería $(NAME)...$(NC)"
	@cp $(LIBFT) $(NAME)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)✓ $(NAME) creada exitosamente$(NC)"

%.o: %.c ft_printf.h
	@echo "$(YELLOW)Compilando $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Eliminando archivos objeto...$(NC)"
	@rm -f $(OBJS)
	@echo "$(GREEN)✓ Archivos objeto eliminados$(NC)"

fclean: clean
	@echo "$(RED)Eliminando $(NAME)...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ $(NAME) eliminada$(NC)"

re: fclean all

bonus: $(NAME)

test: $(NAME)
	@echo "$(YELLOW)Compilando test...$(NC)"
	@$(CC) $(CFLAGS) -L. -lftprintf test.c -o test_printf
	@echo "$(GREEN)✓ Test compilado. Ejecuta con: ./test_printf$(NC)"

norm:
	@echo "$(YELLOW)Verificando norminette...$(NC)"
	@norminette $(SRCS) ft_printf.h

.PHONY: all clean fclean re bonus test norm
