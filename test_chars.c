#include "libft.h"
#include "test.h"
#include <ctype.h>
#include <stdio.h>

void	test_isalpha(char c)
{
	int			expect;
	int			actual;
	FuncStats	*f;
	FILE		*log;

	expect = (isalpha((unsigned char)c) != 0);
	actual = (ft_isalpha((unsigned char)c) != 0);
	f = get_stats("isalpha");
	if (expect == actual)
		f->passed++;
	else
	{
		f->failed++;
		log = fopen("error.log", "a");
		if (log)
		{
			if (isprint((unsigned char)c))
				fprintf(log,
					"isalpha: input='%c' (code=%d) expected=%d actual=%d\n", c,
					(unsigned char)c, expect, actual);
			else
				fprintf(log,
					"isalpha: input=0x%02X          expected=%d actual=%d\n",
					(unsigned char)c, expect, actual);
			fclose(log);
		}
	}
}

void	test_isdigit(char c)
{
	int			expect;
	int			actual;
	FuncStats	*f;
	FILE		*log;

	expect = (isdigit((unsigned char)c) != 0);
	actual = (ft_isdigit((unsigned char)c) != 0);
	f = get_stats("isdigit");
	if (expect == actual)
		f->passed++;
	else
	{
		f->failed++;
		log = fopen("error.log", "a");
		if (log)
		{
			if (isprint((unsigned char)c))
				fprintf(log,
					"isdigit: input='%c' (code=%d) expected=%d actual=%d\n", c,
					(unsigned char)c, expect, actual);
			else
				fprintf(log,
					"isdigit: input=0x%02X          expected=%d actual=%d\n",
					(unsigned char)c, expect, actual);
			fclose(log);
		}
	}
}

void	test_isalnum(char c)
{
	int			expect;
	int			actual;
	FuncStats	*f;
	FILE		*log;

	expect = (isalnum((unsigned char)c) != 0);
	actual = (ft_isalnum((unsigned char)c) != 0);
	f = get_stats("isalnum");
	if (expect == actual)
		f->passed++;
	else
	{
		f->failed++;
		log = fopen("error.log", "a");
		if (log)
		{
			if (isprint((unsigned char)c))
				fprintf(log,
					"isalnum: input='%c' (code=%d) expected=%d actual=%d\n", c,
					(unsigned char)c, expect, actual);
			else
				fprintf(log,
					"isalnum: input=0x%02X          expected=%d actual=%d\n",
					(unsigned char)c, expect, actual);
			fclose(log);
		}
	}
}

void	test_isascii(char c)
{
	int			expect;
	int			actual;
	FuncStats	*f;
	FILE		*log;

	expect = (isascii((unsigned char)c) != 0);
	actual = (ft_isascii((unsigned char)c) != 0);
	f = get_stats("isascii");
	if (expect == actual)
		f->passed++;
	else
	{
		f->failed++;
		log = fopen("error.log", "a");
		if (log)
		{
			if (isprint((unsigned char)c))
				fprintf(log,
					"isascii: input='%c' (code=%d) expected=%d actual=%d\n", c,
					(unsigned char)c, expect, actual);
			else
				fprintf(log,
					"isascii: input=0x%02X          expected=%d actual=%d\n",
					(unsigned char)c, expect, actual);
			fclose(log);
		}
	}
}

void	test_isprint(char c)
{
	int			expect;
	int			actual;
	FuncStats	*f;
	FILE		*log;

	expect = (isprint((unsigned char)c) != 0);
	actual = (ft_isprint((unsigned char)c) != 0);
	f = get_stats("isprint");
	if (expect == actual)
		f->passed++;
	else
	{
		f->failed++;
		log = fopen("error.log", "a");
		if (log)
		{
			if (isprint((unsigned char)c))
				fprintf(log,
					"isprint: input='%c' (code=%d) expected=%d actual=%d\n", c,
					(unsigned char)c, expect, actual);
			else
				fprintf(log,
					"isprint: input=0x%02X          expected=%d actual=%d\n",
					(unsigned char)c, expect, actual);
			fclose(log);
		}
	}
}

void    test_toupper(char c)
{
    int     expect;
    int     actual;
    FuncStats   *f;
    FILE        *log;

    expect = toupper((unsigned char)c);
    actual = ft_toupper((unsigned char)c);
    f = get_stats("toupper");
    if (expect == actual)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            if (isprint((unsigned char)c))
                fprintf(log,
                    "toupper: input='%c' (code=%d) expected='%c' (code=%d) actual='%c' (code=%d)\n",
                    c, (unsigned char)c,
                    (char)expect, expect,
                    (char)actual, actual);
            else
                fprintf(log,
                    "toupper: input=0x%02X          expected=0x%02X actual=0x%02X\n",
                    (unsigned char)c, expect, actual);
            fclose(log);
        }
    }
}

void    test_tolower(char c)
{
    int     expect;
    int     actual;
    FuncStats   *f;
    FILE        *log;

    expect = tolower((unsigned char)c);
    actual = ft_tolower((unsigned char)c);
    f = get_stats("tolower");
    if (expect == actual)
        f->passed++;
    else
    {
        f->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            if (isprint((unsigned char)c))
                fprintf(log,
                    "tolower: input='%c' (code=%d) expected='%c' (code=%d) actual='%c' (code=%d)\n",
                    c, (unsigned char)c,
                    (char)expect, expect,
                    (char)actual, actual);
            else
                fprintf(log,
                    "tolower: input=0x%02X          expected=0x%02X actual=0x%02X\n",
                    (unsigned char)c, expect, actual);
            fclose(log);
        }
    }
}

