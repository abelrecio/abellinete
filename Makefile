# Variables
CC := gcc
CFLAGS := -Wall -Wextra -Werror -D_DEFAULT_SOURCE -I.

# Source and object files
SRCS := bsd_compat.c test_runner.c
OBJS := $(SRCS:.c=.o)
LIBFT := libft.a

# Default target
.PHONY: default
default: tests

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link tests executable
tests: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L. -lft -o tests

# Clean object files
.PHONY: clean
clean:
	rm -f $(OBJS)

# Remove executable and objects
.PHONY: fclean
fclean: clean
	rm -f tests

# Rebuild everything
.PHONY: re
re: fclean default

# Run compilation in Debian Docker to reproduce Debian errors
.PHONY: check-debian
check-debian:
	docker run --rm \
		-v "$$PWD":/src -w /src \
		debian:stable-slim \
		bash -euxc "apt update && apt install -y build-essential && \
			gcc -Wall -Wextra -Werror *.c"


