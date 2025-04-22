#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "test.h"

char	*make_expected_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	substring_len;

	if (NULL == s)
		return (NULL);
	s_len = strlen(s);
	if (start >= s_len)
		return (strdup(""));
	substring_len = s_len - start;
	if (len > substring_len)
		len = substring_len;
	str = malloc(len + 1);
	if (NULL == str)
		return (NULL);
	strlcpy(str, s + start, len + 1);
	return (str);
}


void test_substr(const char *s, unsigned int start, size_t len)
{
    char      *expect = make_expected_substr(s, start, len);
    char      *actual = ft_substr(s, start, len);
    FuncStats *f      = get_stats("substr");
    FILE      *log;

    if (expect != NULL && actual != NULL && strcmp(expect, actual) == 0)
    {
        f->passed++;
    }
    else if (expect == NULL && actual == NULL)
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
                "substr: s=\"%s\", start=%u, len=%zu expected=\"%s\" actual=\"%s\"\n",
                s, start, len,
                expect ? expect : "(null)",
                actual ? actual : "(null)");
            fclose(log);
        }
    }

    free(expect);
    free(actual);
}

void test_strjoin(const char *s1, const char *s2)
{
    char        *expect;
    char        *actual;
    FuncStats   *f;
    FILE        *log;
    size_t       len1 = strlen(s1);
    size_t       len2 = strlen(s2);

    expect = malloc(len1 + len2 + 1);
    if (expect)
    {
        memcpy(expect, s1, len1);
        memcpy(expect + len1, s2, len2 + 1);
    }
    actual = ft_strjoin(s1, s2);
    f = get_stats("strjoin");
    if (expect && actual && strcmp(expect, actual) == 0)
        f->passed++;
    else if (!expect && !actual)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "strjoin: s1=\"%s\", s2=\"%s\" expected=\"%s\" actual=\"%s\"\n",
                s1, s2,
                expect ? expect : "(null)",
                actual ? actual : "(null)");
            fclose(log);
        }
    }
    free(expect);
    free(actual);
}

static char *make_expected_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;
	char	*trimmed;

	if (NULL == s1 || NULL == set)
		return (NULL);
	if (!*s1)
		return (strdup(s1));
	start = 0;
	end = strlen(s1) - 1;
	while (*(s1 + start) && strchr(set, *(s1 + start)))
		++start;
	while (end >= 0 && strchr(set, *(s1 + end)))
		--end;
	if (start > end)
		return (strdup(""));
	trimmed = malloc((end - start) + 2);
	if (NULL == trimmed)
		return (NULL);
	strlcpy(trimmed, s1 + start, (end - start) + 2);
	return (trimmed);
}

void test_strtrim(const char *s1, const char *set)
{
    char      *expect = make_expected_strtrim(s1, set);
    char      *actual = ft_strtrim(s1, set);
    FuncStats *f      = get_stats("strtrim");
    FILE      *log;

    if (expect && actual && strcmp(expect, actual) == 0)
    {
        f->passed++;
    }
    else if (!expect && !actual)
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
                "strtrim: s1=\"%s\", set=\"%s\" expected=\"%s\" actual=\"%s\"\n",
                s1, set,
                expect ? expect : "(null)",
                actual ? actual : "(null)");
            fclose(log);
        }
    }

    free(expect);
    free(actual);
}

int	safe_malloc(char **token_v, int position, size_t buffer)
{
	int		i;

	i = 0;
	token_v[position] = malloc(buffer);
	if (NULL == token_v[position])
	{
		while (i < position)
			free(token_v[i++]);
		free(token_v);
		return (1);
	}
	return (0);
}

int	fill(char **token_v, char const *s, char delimeter)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == delimeter && *s)
			++s;
		while (*s != delimeter && *s)
		{
			++len;
			++s;
		}
		if (len)
		{
			 if (safe_malloc(token_v, i, len + 1))
				   return (1);
		  ft_strlcpy(token_v[i], s - len, len + 1);
		}
		++i;
	}
	return (0);
}

size_t	count_tokens(char const *s, char delimeter)
{
	size_t	tokens;
	int		inside_token;

	tokens = 0;
	while (*s)
	{
		inside_token = 0;
		while (*s == delimeter && *s)
			++s;
		while (*s != delimeter && *s)
		{
			if (!inside_token)
			{
				++tokens;
				inside_token = 42;
			}
			++s;
		}
	}
	return (tokens);
}

char	**make_expected_split(char const *s, char c)
{
	size_t	tokens;
	char	**token_v;

	if (NULL == s)
		return (NULL);
	tokens = 0;
	tokens = count_tokens(s, c);
	token_v = malloc((tokens + 1) * sizeof(char *));
	if (NULL == token_v)
		return (NULL);
	token_v[tokens] = NULL;
	if (fill(token_v, s, c))
		return (NULL);
	return (token_v);
}
void test_split(const char *s, char delim)
{
    char    **expect = make_expected_split(s, delim);
    char    **actual = ft_split(s, delim);
    FuncStats *f    = get_stats("split");
    FILE   *log;
    int ok = 1;
    for (size_t i = 0; ; i++)
    {
        if (!expect[i] && !actual[i]) break;
        if (!expect[i] || !actual[i] || strcmp(expect[i], actual[i]) != 0)
        {
            ok = 0;
            break;
        }
    }

    if (ok)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log, "split: s=\"%s\", delim='%c'\n", s, delim);
            fclose(log);
        }
    }
    for (size_t i = 0; expect && expect[i]; i++) free(expect[i]);
    free(expect);
    for (size_t i = 0; actual && actual[i]; i++) free(actual[i]);
    free(actual);
}



char	*make_expected_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		i;

	i = 0;
	if (NULL == s)
		return (NULL);
	ptr = malloc(ft_strlen(s) + 1);
	if (NULL == ptr)
		return (NULL);
	if (NULL == f)
	{
		ft_strlcpy(ptr, s, ft_strlen(s) + 1);
		return (ptr);
	}
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		++i;
	}
	ptr[i] = '\0';
	return (ptr);
}
void test_strmapi(const char *s, char (*f)(unsigned int, char))
{
    char      *expect = make_expected_strmapi(s, f);
    char      *actual = ft_strmapi(s, f);
    FuncStats *st     = get_stats("strmapi");
    FILE      *log;

    if (expect && actual && strcmp(expect, actual) == 0)
        st->passed++;
    else if (!expect && !actual)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "strmapi: s=\"%s\" expected=\"%s\" actual=\"%s\"\n",
                s,
                expect ? expect : "(null)",
                actual ? actual : "(null)");
            fclose(log);
        }
    }
    free(expect);
    free(actual);
}

void	make_expected_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	if (NULL == s || NULL == f)
		return ;
	while (s[i])
	{
		f(i, s + i);
		++i;
	}
}

void test_striteri(const char *s, void (*f)(unsigned int, char *))
{
    FuncStats *st  = get_stats("striteri");
    FILE      *log;
    char      *expect = strdup(s);
    char      *actual = strdup(s);
    if (!expect || !actual)
    {
        free(expect);
        free(actual);
        st->failed++;
        return;
    }

    make_expected_striteri(expect, f);
    ft_striteri(actual, f);

    if (strcmp(expect, actual) == 0)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "striteri: s=\"%s\", func=%p expected=\"%s\" actual=\"%s\"\n",
                s, (void *)f, expect, actual);
            fclose(log);
        }
    }

    free(expect);
    free(actual);
}
