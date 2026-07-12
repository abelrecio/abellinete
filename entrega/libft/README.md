*This project was created as part of the 42 curriculum by clopez-b.*

## Description 📚

Libft is the first library built in C for 42, and it is basically a custom version of a small standard library. The idea behind it was to stop depending on ready-made functions and really understand what they do under the hood, while also getting more comfortable with pointers, memory management, and writing clean reusable code.

This repository contains the mandatory Libft functions, the extra helper functions asked for in the subject, and the bonus linked-list tools. Everything is compiled into `libft.a`, so it can be reused in later C projects by linking it like a normal static library.

## Instructions

### Build

```bash
make
```

This command compiles everything and generates `libft.a`.

### Clean

```bash
make clean
```

This cleans the object files.

### Full Clean

```bash
make fclean
```

This removes both the object files and the final archive.

### Rebuild

```bash
make re
```

This wipes the build and compiles everything again from zero.

### Using the library in another program

Include the header in your source file:

```c
#include "libft.h"
```

Then compile and link your program against the static library. For example:

```bash
gcc main.c -L. -lft -o program
```

## Library Overview

The library is split into three parts so it stays easier to read and reuse:

### 1. Libc-inspired functions

ft_isalpha, ft_isdigit, ft_isalnum, ft_isascii, ft_isprint, ft_strlen, ft_memset, ft_bzero, ft_memcpy, ft_memmove, ft_strlcpy, ft_strlcat, ft_toupper, ft_tolower, ft_strchr, ft_strrchr, ft_strncmp, ft_memchr, ft_memcmp, ft_strnstr, ft_atoi, ft_strdup.

Additionally, dynamic allocation-related functions:

ft_calloc

### 2. Additional utility functions

This part adds the extra utilities that make the library more useful day to day: dynamic allocation helpers, string editing tools, higher-order string functions, formatted output helpers, and string slicing. It includes functions such as ft_substr, ft_strjoin, ft_strtrim, ft_split, ft_itoa, ft_strmapi, ft_striteri, ft_putchar_fd, ft_putstr_fd, ft_putendl_fd, ft_putnbr_fd.

### 3. Bonus linked-list functions

The bonus part adds a simple singly linked list structure, `t_list`, together with helpers to create, add, delete, iterate, and map list nodes. These functions are ft_lstnew, ft_lstadd_front, ft_lstsize, ft_lstlast, ft_lstadd_back, ft_lstdelone, ft_lstclear, ft_lstiter, ft_lstmap.

## Resources 

The main references I used for this kind of project are:

- `man 3` pages for standard C library functions.
- `man 7 string` for string handling conventions and behavior.
- The official C language documentation and references such as cppreference.
- The C Handbook by Flavio Copes.
- The 42 Libft subject documentation.

### Use of AI

AI was only used to write the `main` in files in order to save time. It was not used to implement the library functions or to design the project itself.

## Additional Notes

This project is the base for future 42 C projects. The code is split into small, reusable functions on purpose, because that makes it easier to maintain and to extend later.
