#ifndef TEST_H
#define TEST_H

#include <stddef.h>

typedef struct {
    char   name[32];
    size_t passed;
    size_t failed;
} FuncStats;

extern FuncStats *stats;
extern size_t    stats_count;
extern size_t    stats_cap;

size_t  strlcpy(char *dst, const char *src, size_t dstsize);
size_t  strlcat(char *dst, const char *src, size_t dstsize);
char   *strnstr(const char *haystack, const char *needle, size_t len);



FuncStats *get_stats(const char *func_name);
void       test_isalpha(char c);
void       test_isdigit(char c);
void	test_isalnum(char c);
void	test_isascii(char c);
void	test_isprint(char c);
void    test_toupper(char c);
void    test_tolower(char c);
void    test_strchr(const char *s, int c);
void    test_strrchr(const char *s, int c);
void    test_strlen(const char *s);
void    test_strncmp(const char *s1, const char *s2, size_t n);
void    test_strlcat(const char *dst_init, const char *src, size_t size);
void test_strlcpy(const char *src, size_t size);
void    test_memset(const char *init, int c, size_t n);
void    test_bzero(const char *init, size_t n);
void    test_memchr(const char *s, int c, size_t n);
void    test_memcmp(const char *s1, const char *s2, size_t n);
void    test_memcpy(const char *dst_init, const char *src, size_t n);
void    test_memmove(const char *dst_init, const char *src, size_t n);
void    test_atoi(const char *s);
void    test_calloc(size_t nmemb, size_t size);
void    test_strdup(const char *s);
void    test_strnstr(const char *haystack, const char *needle, size_t len);
void test_substr(const char *s, unsigned int start, size_t len);
void test_strjoin(const char *s1, const char *s2);
void test_strtrim(const char *s1, const char *set);
void test_split(const char *s, char delim);
void test_itoa(int n);
void test_strmapi(const char *s, char (*f)(unsigned int, char));
void test_striteri(const char *s, void (*f)(unsigned int, char *));
void    test_putchar_fd(char c, int fd);
void    test_putstr_fd(const char *s, int fd);
void    test_putendl_fd(const char *s, int fd);
void    test_putnbr_fd(int n, int fd);
void    test_lstnew(const char *spec);
void    test_lstadd_front(const char *spec, const char *newc);
void    test_lstadd_back(const char *spec, const char *newc);
void    test_lstsize(const char *spec);
void    test_lstlast(const char *spec);
void    test_lstdelone(const char *spec, const char *del_name);
void    test_lstclear(const char *spec, const char *del_name);
void    test_lstiter(const char *spec, const char *func_name);
void    test_lstmap(const char *spec, const char *func_name, const char *del_name);

#endif

