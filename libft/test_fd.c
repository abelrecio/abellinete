#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "test.h"

void    test_putchar_fd(char c, int fd)
{
    char            expect;
    char            actual;
    FuncStats      *f;
    FILE           *log;
    int             p1[2], p2[2];

	if (fd)
		fd = 1;
    pipe(p1);
    pipe(p2);
    write(p1[1], &c, 1);
    ft_putchar_fd(c, p2[1]);
    read(p1[0], &expect, 1);
    read(p2[0], &actual, 1);
    f = get_stats("putchar_fd");
    if (expect == actual)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "putchar_fd: input='%c' (code=%d) expected='%c' actual='%c'\n",
                c, (unsigned char)c, expect, actual);
            fclose(log);
        }
    }
    close(p1[0]); close(p1[1]);
    close(p2[0]); close(p2[1]);
}

void    test_putstr_fd(const char *s, int fd)
{
    size_t          len = strlen(s);
    char           *expect = malloc(len + 1);
    char           *actual = malloc(len + 1);
    FuncStats      *f;
    FILE           *log;
    int             p1[2], p2[2];

	        if (fd)
                fd = 1;

    pipe(p1);
    pipe(p2);
    write(p1[1], s, len);
    ft_putstr_fd((char *)s, p2[1]);
    read(p1[0], expect, len);
    read(p2[0], actual, len);
    expect[len] = '\0';
    actual[len] = '\0';
    f = get_stats("putstr_fd");
    if (strcmp(expect, actual) == 0)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "putstr_fd: input=\"%s\" expected=\"%s\" actual=\"%s\"\n",
                s, expect, actual);
            fclose(log);
        }
    }
    free(expect);
    free(actual);
    close(p1[0]); close(p1[1]);
    close(p2[0]); close(p2[1]);
}

void    test_putendl_fd(const char *s, int fd)
{
    size_t          len = strlen(s) + 1;
    char           *expect = malloc(len + 1);
    char           *actual = malloc(len + 1);
    FuncStats      *f;
    FILE           *log;
    int             p1[2], p2[2];

        if (fd)
                fd = 1;

    pipe(p1);
    pipe(p2);
    write(p1[1], s, len - 1);
    write(p1[1], "\n", 1);
    ft_putendl_fd((char *)s, p2[1]);
    read(p1[0], expect, len);
    read(p2[0], actual, len);
    expect[len] = actual[len] = '\0';
    f = get_stats("putendl_fd");
    if (strcmp(expect, actual) == 0)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "putendl_fd: input=\"%s\" expected=\"%s\" actual=\"%s\"\n",
                s, expect, actual);
            fclose(log);
        }
    }
    free(expect);
    free(actual);
    close(p1[0]); close(p1[1]);
    close(p2[0]); close(p2[1]);
}

void    test_putnbr_fd(int n, int fd)
{
    char            expect_buf[32];
    char           *actual = malloc(32);
    FuncStats      *f;
    FILE           *log;
    int             p1[2], p2[2];
    size_t          len;

        if (fd)
                fd = 1;
    sprintf(expect_buf, "%d", n);
    len = strlen(expect_buf);
    pipe(p1);
    pipe(p2);
    write(p1[1], expect_buf, len);
    ft_putnbr_fd(n, p2[1]);
    read(p2[0], actual, len);
    actual[len] = '\0';
    f = get_stats("putnbr_fd");
    if (strncmp(expect_buf, actual, len) == 0)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "putnbr_fd: input=%d expected=\"%s\" actual=\"%s\"\n",
                n, expect_buf, actual);
            fclose(log);
        }
    }
    free(actual);
    close(p1[0]); close(p1[1]);
    close(p2[0]); close(p2[1]);
}

