#include <stdio.h>
#include "libft.h"
#include "test.h"
#include <string.h>

void    test_strchr(const char *s, int c)
{
    char        *expect;
    char        *actual;
    FuncStats   *f;
    FILE        *log;

    expect = strchr(s, c);
    actual = ft_strchr(s, c);
    f = get_stats("strchr");
    if (expect == actual)
    {
        f->passed++;
    }
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            if (expect && actual)
            {
                fprintf(log,
                    "strchr: input=\"%s\", search='%c' (code=%d) expected_idx=%td actual_idx=%td\n",
                    s, (char)c, c,
                    expect - s,
                    actual - s);
            }
            else
            {
                fprintf(log,
                    "strchr: input=\"%s\", search='%c' (code=%d) expected=%p actual=%p\n",
                    s, (char)c, c,
                    (void *)expect,
                    (void *)actual);
            }
            fclose(log);
        }
    }
}

void    test_strrchr(const char *s, int c)
{
    char        *expect;
    char        *actual;
    FuncStats   *f;
    FILE        *log;

    expect = strrchr(s, c);
    actual = ft_strrchr(s, c);
    f = get_stats("strrchr");
    if (expect == actual)
    {
        f->passed++;
    }
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            if (expect && actual)
            {
                fprintf(log,
                    "strrchr: input=\"%s\", search='%c' (code=%d) expected_idx=%td actual_idx=%td\n",
                    s, (char)c, c,
                    expect - s,
                    actual - s);
            }
            else
            {
                fprintf(log,
                    "strrchr: input=\"%s\", search='%c' (code=%d) expected=%p actual=%p\n",
                    s, (char)c, c,
                    (void *)expect,
                    (void *)actual);
            }
            fclose(log);
        }
    }
}

void    test_strlen(const char *s)
{
    size_t      expect;
    size_t      actual;
    FuncStats   *f;
    FILE        *log;

    expect = strlen(s);
    actual = ft_strlen(s);
    f = get_stats("strlen");
    if (expect == actual)
    {
        f->passed++;
    }
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "strlen: input=\"%s\" expected=%zu actual=%zu\n",
                s,
                expect,
                actual);
            fclose(log);
        }
    }
}

void    test_strncmp(const char *s1, const char *s2, size_t n)
{
    int         expect;
    int         actual;
    FuncStats  *f;
    FILE       *log;

    expect = strncmp(s1, s2, n);
    actual = ft_strncmp(s1, s2, n);
    f = get_stats("strncmp");
    if (expect == actual)
    {
        f->passed++;
    }
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "strncmp: s1=\"%s\", s2=\"%s\", n=%zu expected=%d actual=%d\n",
                s1, s2, n, expect, actual);
            fclose(log);
        }
    }
}

void    test_strlcat(const char *dst_init, const char *src, size_t size)
{
    #define BUF_SZ 256
    char        buf1[BUF_SZ];
    char        buf2[BUF_SZ];
    size_t      expect;
    size_t      actual;
    FuncStats  *f;
    FILE       *log;
    size_t      init_len = strlen(dst_init);

    memset(buf1, 'A', BUF_SZ);
    memset(buf2, 'A', BUF_SZ);
    memcpy(buf1, dst_init, init_len + 1);
    memcpy(buf2, dst_init, init_len + 1);

    expect = strlcat(buf1, src, size);
    actual = ft_strlcat(buf2, src, size);
    f = get_stats("strlcat");
    if (expect == actual && memcmp(buf1, buf2, BUF_SZ) == 0)
    {
        f->passed++;
    }
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "strlcat: dst_init=\"%s\", src=\"%s\", size=%zu expected_ret=%zu actual_ret=%zu\n",
                dst_init, src, size, expect, actual);
            fprintf(log,
                "    dest_expect=\"%s\" dest_actual=\"%s\"\n",
                buf1, buf2);
            fclose(log);
        }
    }
    #undef BUF_SZ
}


void    test_strlcpy(const char *src, size_t size)
{
    #define BUF_SZ 256
    char        buf1[BUF_SZ];
    char        buf2[BUF_SZ];
    size_t      expect;
    size_t      actual;
    FuncStats  *f;
    FILE       *log;

    memset(buf1, 'A', BUF_SZ);
    memset(buf2, 'A', BUF_SZ);

    expect = strlcpy(buf1, src, size);
    actual = ft_strlcpy(buf2, src, size);
    f = get_stats("strlcpy");

    if (expect == actual && memcmp(buf1, buf2, BUF_SZ) == 0)
    {
        f->passed++;
    }
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "strlcpy: src=\"%s\", size=%zu expected_ret=%zu actual_ret=%zu\n",
                src, size, expect, actual);
            fprintf(log,
                "    dest_expect=\"%.*s\" dest_actual=\"%.*s\"\n",
                (int)(size > 0 ? size - 1 : 0), buf1,
                (int)(size > 0 ? size - 1 : 0), buf2);
            fclose(log);
        }
    }
    #undef BUF_SZ
}

void    test_atoi(const char *s)
{
    int         expect = atoi(s);
    int         actual = ft_atoi(s);
    FuncStats  *f      = get_stats("atoi");
    FILE       *log;

    if (expect == actual)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "atoi: input=\"%s\" expected=%d actual=%d\n",
                s, expect, actual);
            fclose(log);
        }
    }
}

void    test_strdup(const char *s)
{
    char      *expect = strdup(s);
    char      *actual = ft_strdup(s);
    FuncStats *f      = get_stats("strdup");
    FILE      *log;

    if (expect && actual)
    {
        if (strcmp(expect, actual) == 0)
            f->passed++;
        else
        {
            f->failed++;
            log = fopen("error.log", "a");
            if (log)
            {
                fprintf(log,
                    "strdup: input=\"%s\" expected=\"%s\" actual=\"%s\"\n",
                    s, expect, actual);
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
                "strdup: input=\"%s\" expected_ptr=%p actual_ptr=%p\n",
                s, (void*)expect, (void*)actual);
            fclose(log);
        }
    }
    free(expect);
    free(actual);
}

extern char *strnstr(const char *haystack, const char *needle, size_t len);

void    test_strnstr(const char *haystack, const char *needle, size_t len)
{
    char        *expect;
    char        *actual;
    FuncStats   *f;
    FILE        *log;

    expect = strnstr(haystack, needle, len);
    actual = ft_strnstr(haystack, needle, len);
    f = get_stats("strnstr");
    if (expect == actual)
    {
        f->passed++;
    }
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            if (expect && actual)
            {
                fprintf(log,
                    "strnstr: hay=\"%s\", ned=\"%s\", len=%zu expected_idx=%td actual_idx=%td\n",
                    haystack, needle, len,
                    expect - haystack,
                    actual - haystack);
            }
            else
            {
                fprintf(log,
                    "strnstr: hay=\"%s\", ned=\"%s\", len=%zu expected=%p actual=%p\n",
                    haystack, needle, len,
                    (void *)expect,
                    (void *)actual);
            }
            fclose(log);
        }
    }
}



void test_itoa(int n)
{
    char       expect_buf[12]; 
    char      *actual;
    FuncStats *f = get_stats("itoa");
    FILE      *log;

    sprintf(expect_buf, "%d", n);

    actual = ft_itoa(n);
    if (actual && strcmp(expect_buf, actual) == 0)
    {
        f->passed++;
    }
    else if (!actual)
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "itoa: n=%d expected=\"%s\" actual=(null)\n",
                n, expect_buf);
            fclose(log);
        }
    }
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "itoa: n=%d expected=\"%s\" actual=\"%s\"\n",
                n, expect_buf, actual);
            fclose(log);
        }
    }

    free(actual);
}
