#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FuncStats	*stats = NULL;
size_t		stats_count = 0;
size_t		stats_cap = 0;

FuncStats	*get_stats(const char *func_name)
{
	FuncStats	*f;

	for (size_t i = 0; i < stats_count; i++)
		if (strcmp(stats[i].name, func_name) == 0)
			return (&stats[i]);
	if (stats_count == stats_cap)
	{
		stats_cap = stats_cap ? stats_cap * 2 : 8;
		stats = realloc(stats, stats_cap * sizeof *stats);
	}
	f = &stats[stats_count++];
	strncpy(f->name, func_name, sizeof f->name - 1);
	f->name[sizeof f->name - 1] = '\0';
	f->passed = f->failed = 0;
	return (f);
}
