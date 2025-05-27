#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include "test.h"

void test_memset(const char *init, int c, size_t n)
{
    #define BUF_SZ 256
    unsigned char buf1[BUF_SZ], buf2[BUF_SZ];
    FuncStats *f = get_stats("memset");
    FILE *log;

    memset(buf1, 0xAA, BUF_SZ);
    memset(buf2, 0xAA, BUF_SZ);
    memcpy(buf1, init, strlen(init) + 1);
    memcpy(buf2, init, strlen(init) + 1);

    memset(buf1, c, n);
    ft_memset(buf2, c, n);

    if (memcmp(buf1, buf2, BUF_SZ) == 0)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "memset: init=\"%s\", c=%d, n=%zu\n",
                init, c, n);
            fclose(log);
        }
    }
    #undef BUF_SZ
}

void test_bzero(const char *init, size_t n)
{
    #define BUF_SZ 256
    unsigned char buf1[BUF_SZ], buf2[BUF_SZ];
    FuncStats *f = get_stats("bzero");
    FILE *log;

    memset(buf1, 0xAA, BUF_SZ);
    memset(buf2, 0xAA, BUF_SZ);
    memcpy(buf1, init, strlen(init) + 1);
    memcpy(buf2, init, strlen(init) + 1);

    bzero(buf1, n);
    ft_bzero(buf2, n);

    if (memcmp(buf1, buf2, BUF_SZ) == 0)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "bzero: init=\"%s\", n=%zu\n",
                init, n);
            fclose(log);
        }
    }
    #undef BUF_SZ
}

void test_memcpy(const char *dst_init, const char *src, size_t n)
{
    #define BUF_SZ 256
    unsigned char buf1[BUF_SZ], buf2[BUF_SZ];
    FuncStats *f = get_stats("memcpy");
    FILE *log;

    memset(buf1, 0xAA, BUF_SZ);
    memset(buf2, 0xAA, BUF_SZ);
    memcpy(buf1, dst_init, strlen(dst_init) + 1);
    memcpy(buf2, dst_init, strlen(dst_init) + 1);

    memcpy(buf1, src, n);
    ft_memcpy(buf2, src, n);

    if (memcmp(buf1, buf2, BUF_SZ) == 0)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "memcpy: dst_init=\"%s\", src=\"%s\", n=%zu\n",
                dst_init, src, n);
            fclose(log);
        }
    }
    #undef BUF_SZ
}

void test_memmove(const char *dst_init, const char *src, size_t n)
{
    #define BUF_SZ 256
    unsigned char buf1[BUF_SZ], buf2[BUF_SZ];
    FuncStats *f = get_stats("memmove");
    FILE *log;

    memset(buf1, 0xAA, BUF_SZ);
    memset(buf2, 0xAA, BUF_SZ);
    memcpy(buf1, dst_init, strlen(dst_init) + 1);
    memcpy(buf2, dst_init, strlen(dst_init) + 1);

    memmove(buf1, src, n);
    ft_memmove(buf2, src, n);

    if (memcmp(buf1, buf2, BUF_SZ) == 0)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "memmove: dst_init=\"%s\", src=\"%s\", n=%zu\n",
                dst_init, src, n);
            fclose(log);
        }
    }
    #undef BUF_SZ
}

void test_memchr(const char *s, int c, size_t n)
{
    const void *expect = memchr(s, c, n);
    const void *actual = ft_memchr(s, c, n);
    FuncStats *f = get_stats("memchr");
    FILE *log;

    if (expect == actual)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "memchr: s=\"%s\", c=%d, n=%zu expected=%p actual=%p\n",
                s, c, n, expect, actual);
            fclose(log);
        }
    }
}

void test_memcmp(const char *s1, const char *s2, size_t n)
{
    int expect = memcmp(s1, s2, n);
    int actual = ft_memcmp(s1, s2, n);
    FuncStats *f = get_stats("memcmp");
    FILE *log;

    if ((expect == 0 && actual == 0) ||
        (expect < 0 && actual < 0) ||
        (expect > 0 && actual > 0))
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "memcmp: s1=\"%s\", s2=\"%s\", n=%zu expected=%d actual=%d\n",
                s1, s2, n, expect, actual);
            fclose(log);
        }
    }
}


void    test_calloc(size_t nmemb, size_t size)
{
    void      *expect;
    void      *actual;
    FuncStats *f      = get_stats("calloc");
    FILE      *log;
    size_t     total = nmemb * size;

    expect = calloc(nmemb, size);
    actual = ft_calloc(nmemb, size);
    if (expect && actual)
    {
        if (memcmp(expect, actual, total) == 0)
            f->passed++;
        else
        {
            f->failed++;
            log = fopen("error.log", "a");
            if (log)
            {
                fprintf(log,
                    "calloc: nmemb=%zu, size=%zu mismatch in zeroed region\n",
                    nmemb, size);
                fclose(log);
            }
        }
    }
    else if (expect == actual)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "calloc: nmemb=%zu, size=%zu expected=%p actual=%p\n",
                nmemb, size, expect, actual);
            fclose(log);
        }
    }
    free(expect);
    free(actual);
}
