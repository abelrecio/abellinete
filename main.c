#include <ctype.h>
#include "libft.h"
#include "test.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char map_to_upper(unsigned int i, char c)
{
    (void)i;
    return (char)toupper((unsigned char)c);
}

static char map_to_lower(unsigned int i, char c)
{
    (void)i;
    return (char)tolower((unsigned char)c);
}

static void iter_to_upper(unsigned int i, char *c)
{
    *c = map_to_upper(i, *c);
}

static void iter_to_lower(unsigned int i, char *c)
{
    *c = map_to_lower(i, *c);
}


static void what_function(char *line)
{
    char    *colon;
    char    *func;
    char    *args;
    char    *comma1;
    char     arg;
    char    *param1;
    char    *rest;
    char    *comma2;
    char    *param2;
    char    *param3;

    colon = strchr(line, ':');
    if (!colon)
        return;
    *colon = '\0';
    func = line;
    args = colon + 1;

    comma1 = strchr(args, ',');
    if (!comma1)
    {
        if (*args == '\0')
            return;
        arg = (char)atoi(args);
        if (strcmp(func, "isalpha") == 0)
            test_isalpha(arg);
        else if (strcmp(func, "isdigit") == 0)
            test_isdigit(arg);
        else if (strcmp(func, "isalnum") == 0)
            test_isalnum(arg);
        else if (strcmp(func, "isprint") == 0)
            test_isprint(arg);
        else if (strcmp(func, "isascii") == 0)
            test_isascii(arg);
        else if (strcmp(func, "toupper") == 0)
            test_toupper(arg);
        else if (strcmp(func, "tolower") == 0)
            test_tolower(arg);
        else if (strcmp(func, "strlen") == 0)
            test_strlen(args);
        else if (strcmp(func, "atoi") == 0)
            test_atoi(args);
        else if (strcmp(func, "strdup") == 0)
            test_strdup(args);
        else if (strcmp(func, "itoa") == 0)
            test_itoa(atoi(args));
	return;
    }

    *comma1 = '\0';
    param1 = args;
    rest   = comma1 + 1;
    comma2 = strchr(rest, ',');
    if (comma2)
    {
        *comma2 = '\0';
        param2 = rest;
        param3 = comma2 + 1;

        if (strcmp(func, "strncmp") == 0)
            test_strncmp(param1, param2, (size_t)atoi(param3));
        else if (strcmp(func, "strlcat") == 0)
            test_strlcat(param1, param2, (size_t)atoi(param3));
        else if (strcmp(func, "memset") == 0)
            test_memset(param1, atoi(param2), (size_t)atoi(param3));
        else if (strcmp(func, "memchr") == 0)
            test_memchr(param1, atoi(param2), (size_t)atoi(param3));
        else if (strcmp(func, "memcmp") == 0)
            test_memcmp(param1, param2, (size_t)atoi(param3));
        else if (strcmp(func, "memcpy") == 0)
            test_memcpy(param1, param2, (size_t)atoi(param3));
        else if (strcmp(func, "memmove") == 0)
            test_memmove(param1, param2, (size_t)atoi(param3));
        else if (strcmp(func, "strnstr") == 0)
            test_strnstr(param1, param2, (size_t)atoi(param3));
        else if (strcmp(func, "substr") == 0)
            test_substr(param1, (unsigned int)atoi(param2), (size_t)atoi(param3));
        return;
    }

    param2 = rest;
    if (strcmp(func, "strchr") == 0)
        test_strchr(param1, atoi(param2));
    else if (strcmp(func, "strlcpy") == 0)
        test_strlcpy(param1, (size_t)atoi(param2));
    else if (strcmp(func, "strrchr") == 0)
        test_strrchr(param1, atoi(param2));
    else if (strcmp(func, "strlcpy") == 0)
        test_strlcpy(param1, (size_t)atoi(param2));
    else if (strcmp(func, "bzero") == 0)
        test_bzero(param1, (size_t)atoi(param2));
    else if (strcmp(func, "strtrim") == 0)
        test_strtrim(param1, param2);
    else if (strcmp(func, "calloc") == 0)
        test_calloc((size_t)atoi(param1), (size_t)atoi(param2));
    else if (strcmp(func, "strjoin") == 0)
        test_strjoin(param1, param2);
    else if (strcmp(func, "split") == 0)
        test_split(param1, param2[0]);
    else if (strcmp(func, "putchar_fd") == 0)
        test_putchar_fd(param1[0], atoi(param2));
    else if (strcmp(func, "putstr_fd") == 0)
        test_putstr_fd(param1, atoi(param2));
    else if (strcmp(func, "putendl_fd") == 0)
        test_putendl_fd(param1, atoi(param2));
    else if (strcmp(func, "putnbr_fd") == 0)
        test_putnbr_fd(atoi(param1), atoi(param2));
else if (strcmp(func, "strmapi") == 0)
{
    char (*fptr)(unsigned int, char) = NULL;
    if (strcmp(param2, "toupper") == 0)
        fptr = map_to_upper;
    else if (strcmp(param2, "tolower") == 0)
        fptr = map_to_lower;
    if (fptr)
        test_strmapi(param1, fptr);
}
else if (strcmp(func, "striteri") == 0)
{
    void (*fptr)(unsigned int, char *) = NULL;
    if (strcmp(param2, "toupper") == 0)
        fptr = iter_to_upper;
    else if (strcmp(param2, "tolower") == 0)
        fptr = iter_to_lower;
    if (fptr)
        test_striteri(param1, fptr);
}
	return;
}

static void	process_file(FILE *f)
{
	char	*line;
	size_t	len;
	ssize_t	nread;

	line = NULL;
	len = 0;
	while ((nread = getline(&line, &len, f)) != -1)
	{
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		what_function(line);
	}
	free(line);
}

void	print_summary(void)
{
	printf("┌────────────────┬─────────┬───────┐\n");
	printf("│ %-15s │ %7s │ %5s │\n", "Función", "OK", "KO");
	printf("├────────────────┼─────────┼───────┤\n");
	for (size_t i = 0; i < stats_count; i++)
		printf("│ %-14s │ %7zu │ %5zu │\n", stats[i].name, stats[i].passed,
			stats[i].failed);
	printf("└────────────────┴─────────┴───────┘\n");
}
int	main(int argc, char *argv[])
{
	DIR				*d;
	struct dirent	*ent;
	FILE			*f;

	if (chdir("test_files") != 0)
	{
		perror("chdir(\"test_files\")");
		return (EXIT_FAILURE);
	}
	remove("error.log");
	if (argc == 1)
	{
		d = opendir(".");
		if (!d)
		{
			perror("opendir");
			return (EXIT_FAILURE);
		}
		while ((ent = readdir(d)) != NULL)
		{
			if (ent->d_name[0] == '.')
				continue ;
			f = fopen(ent->d_name, "r");
			if (!f)
			{
				perror(ent->d_name);
				continue ;
			}
			process_file(f);
			fclose(f);
		}
		closedir(d);
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			f = fopen(argv[i], "r");
			if (!f)
			{
				perror(argv[i]);
				continue ;
			}
			process_file(f);
			fclose(f);
		}
	}
	print_summary();
	free(stats);
	return (EXIT_SUCCESS);
}
