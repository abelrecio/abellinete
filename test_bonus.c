#include "libft.h"
#include "test.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void	test_lstnew(void *content)
{
	FuncStats	*st;
	t_list		*node;
	FILE		*log;

	st = get_stats("lstnew");
	node = ft_lstnew(content);
	if (node == NULL)
	{
		st->failed++;
		return ;
	}
	if (node->next == NULL)
		st->passed++;
	else
	{
		st->failed++;
		log = fopen("error.log", "a");
		if (log)
		{
			fprintf(log, "lstnew: content=%p, expected content=%p; next expected=NULL, actual next=%p\n", node->content, content, node->next);
			fclose(log);
		}
	}
	free(node);
}


void test_lstadd_front(void)
{
    FuncStats *st = get_stats("lstadd_front");
    t_list    *list = NULL;
    t_list    *node1;
    t_list    *node2;
    FILE      *log;

    node1 = ft_lstnew("first");
    if (!node1)
    {
        st->failed++;
        return;
    }

    ft_lstadd_front(&list, node1);
    if (list == node1 && list->next == NULL)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstadd_front (empty): expected head=%p, got=%p; next=NULL check failed\n",
                (void*)node1, (void*)list);
            fclose(log);
        }
    }

    node2 = ft_lstnew("second");
    if (!node2)
    {
        free(list);
        st->failed++;
        return;
    }

    ft_lstadd_front(&list, node2);
    if (list == node2 && list->next == node1)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstadd_front (non-empty): expected head=%p, got=%p; next should be %p, got %p\n",
                (void*)node2, (void*)list,
                (void*)node1,
                (void*)list->next);
            fclose(log);
        }
    }

    free(node2);
    free(node1);
}

void test_lstsize(void)
{
    FuncStats *st = get_stats("lstsize");
    t_list    *list = NULL;
    t_list    *node1;
    t_list    *node2;
    int        size;
    FILE      *log;

    size = ft_lstsize(list);
    if (size == 0)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstsize (empty): expected 0, got %d\n",
                size);
            fclose(log);
        }
    }

    node1 = ft_lstnew("first");
    if (!node1)
    {
        st->failed++;
        return;
    }
    list = node1;
    size = ft_lstsize(list);
    if (size == 1)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstsize (one node): expected 1, got %d\n",
                size);
            fclose(log);
        }
    }

    node2 = ft_lstnew("second");
    if (!node2)
    {
        free(node1);
        st->failed++;
        return;
    }
    ft_lstadd_front(&list, node2);
    size = ft_lstsize(list);
    if (size == 2)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstsize (two nodes): expected 2, got %d\n",
                size);
            fclose(log);
        }
    }

    free(node2);
    free(node1);
}

void test_lstlast(void)
{
    FuncStats *st = get_stats("lstlast");
    t_list    *list = NULL;
    t_list    *node1;
    t_list    *node2;
    t_list    *last;
    FILE      *log;

    last = ft_lstlast(NULL);
    if (last == NULL)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstlast (NULL list): expected NULL, got %p\n",
                (void*)last);
            fclose(log);
        }
    }

    node1 = ft_lstnew("first");
    if (!node1)
    {
        st->failed++;
        return;
    }

    list = node1;
    last = ft_lstlast(list);
    if (last == node1)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstlast (1 node): expected %p, got %p\n",
                (void*)node1, (void*)last);
            fclose(log);
        }
    }

    node2 = ft_lstnew("second");
    if (!node2)
    {
        free(node1);
        st->failed++;
        return;
    }
    node1->next = node2; 

    last = ft_lstlast(list);
    if (last == node2)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstlast (2 nodes): expected %p, got %p\n",
                (void*)node2, (void*)last);
            fclose(log);
        }
    }

    free(node2);
    free(node1);
}


void test_lstadd_back(void)
{
    FuncStats *st = get_stats("lstadd_back");
    t_list    *list = NULL;
    t_list    *node1;
    t_list    *node2;
    FILE      *log;

    node1 = ft_lstnew("first");
    if (!node1)
    {
        st->failed++;
        return;
    }
    ft_lstadd_back(&list, node1);
    if (list == node1 && node1->next == NULL)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstadd_back (empty): expected head=%p with next=NULL, got head=%p next=%p\n",
                (void*)node1, (void*)list, (void*)(list ? list->next : NULL));
            fclose(log);
        }
    }

    node2 = ft_lstnew("second");
    if (!node2)
    {
        free(node1);
        st->failed++;
        return;
    }
    ft_lstadd_back(&list, node2);
    if (list == node1 && node1->next == node2 && node2->next == NULL)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstadd_back (non-empty): expected head=%p next=%p, got head=%p next=%p\n",
                (void*)node1, (void*)node2,
                (void*)list, (void*)(list ? list->next : NULL));
            fclose(log);
        }
    }

    free(node2);
    free(node1);
}

static int g_del_count;

void del_counting(void *content)
{
    free(content);
    g_del_count++;
}

void test_lstdelone(void)
{
    FuncStats *st = get_stats("lstdelone");
    t_list    *node1;
    t_list    *node2;
    FILE      *log;

    g_del_count = 0;
    char *c1 = strdup("first");
    if (!c1)
    {
        st->failed++;
        return;
    }
    node1 = ft_lstnew(c1);
    if (!node1)
    {
        free(c1);
        st->failed++;
        return;
    }
    ft_lstdelone(node1, del_counting);
    if (g_del_count == 1)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstdelone (single): del called %d times, expected 1\n", g_del_count);
            fclose(log);
        }
    }

    g_del_count = 0;
    char *c2 = strdup("first");
    char *c3 = strdup("second");
    if (!c2 || !c3)
    {
        free(c2);
        free(c3);
        st->failed++;
        return;
    }
    node1 = ft_lstnew(c2);
    node2 = ft_lstnew(c3);
    if (!node1 || !node2)
    {
        free(c2);
        free(c3);
        free(node1);
        free(node2);
        st->failed++;
        return;
    }
    node1->next = node2;
    ft_lstdelone(node1, del_counting);
    if (g_del_count == 1 && node2->content && strcmp((char *)node2->content, "second") == 0)
    {
        st->passed++;
    }
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstdelone (two nodes): del called %d times, expected 1; "
                "second content = \"%s\"\n", g_del_count, node2->content ? (char*)node2->content : "NULL");
            fclose(log);
        }
    }

    free(node2->content);
    free(node2);
}

void test_lstclear(void)
{
    FuncStats *st = get_stats("lstclear");
    t_list    *list = NULL;
    t_list    *n1, *n2, *n3;
    FILE      *log;

    g_del_count = 0;
    ft_lstclear(&list, del_counting);
    if (list == NULL && g_del_count == 0)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstclear (empty): expected list=NULL and del calls=0; got list=%p del=%d\n",
                (void*)list, g_del_count);
            fclose(log);
        }
    }

    char *c1 = strdup("one");
    char *c2 = strdup("two");
    char *c3 = strdup("three");
    if (!c1 || !c2 || !c3)
    {
        free(c1); free(c2); free(c3);
        st->failed++;
        return;
    }
    n1 = ft_lstnew(c1);
    n2 = ft_lstnew(c2);
    n3 = ft_lstnew(c3);
    if (!n1 || !n2 || !n3)
    {
        free(c1); free(c2); free(c3);
        free(n1); free(n2); free(n3);
        st->failed++;
        return;
    }
    n1->next = n2;
    n2->next = n3;
    list = n1;

    g_del_count = 0;
    ft_lstclear(&list, del_counting);
    if (list == NULL && g_del_count == 3)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstclear (3 nodes): expected list=NULL and del calls=3; got list=%p del=%d\n",
                (void*)list, g_del_count);
            fclose(log);
        }
    }
}


static int g_iter_count;

void iter_counting(void *content)
{
    (void)content;
    g_iter_count++;
}

void incr_content(void *content)
{
    (*(int *)content)++;
}

void test_lstiter(void)
{
    FuncStats *st = get_stats("lstiter");
    t_list    *list = NULL;
    t_list    *n1, *n2, *n3;
    int       *c1, *c2, *c3;
    FILE      *log;

    g_iter_count = 0;
    ft_lstiter(list, iter_counting);
    if (g_iter_count == 0)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstiter (NULL): expected 0 calls, got %d\n",
                g_iter_count);
            fclose(log);
        }
    }

    c1 = malloc(sizeof(*c1));
    c2 = malloc(sizeof(*c2));
    c3 = malloc(sizeof(*c3));
    if (!c1 || !c2 || !c3)
    {
        free(c1); free(c2); free(c3);
        st->failed++;
        return;
    }
    *c1 = 1; *c2 = 2; *c3 = 3;
    n1 = ft_lstnew(c1);
    n2 = ft_lstnew(c2);
    n3 = ft_lstnew(c3);
    if (!n1 || !n2 || !n3)
    {
        free(c1); free(c2); free(c3);
        free(n1); free(n2); free(n3);
        st->failed++;
        return;
    }
    n1->next = n2;
    n2->next = n3;
    list = n1;

    g_iter_count = 0;
    ft_lstiter(list, iter_counting);
    if (g_iter_count == 3)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstiter (count): expected 3 calls, got %d\n",
                g_iter_count);
            fclose(log);
        }
    }

    ft_lstiter(list, incr_content);
    if (*c1 == 2 && *c2 == 3 && *c3 == 4)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstiter (modify): expected [2,3,4], got [%d,%d,%d]\n",
                *c1, *c2, *c3);
            fclose(log);
        }
    }

    free(c1); free(c2); free(c3);
    free(n3); free(n2); free(n1);
}



void *f_double(void *content)
{
    int *x = malloc(sizeof(*x));
    if (!x)
        return NULL;
    *x = (*(int *)content) * 2;
    return x;
}

void *f_fail_on_two(void *content)
{
    if (*(int *)content == 2)
        return NULL;
    int *x = malloc(sizeof(*x));
    if (!x)
        return NULL;
    *x = *(int *)content;
    return x;
}

void test_lstmap(void)
{
    FuncStats *st = get_stats("lstmap");
    t_list *list = NULL;
    t_list *n1, *n2, *n3;
    t_list *mapped;
    int *i1, *i2, *i3;
    FILE *log;
    int ok;

    mapped = ft_lstmap(NULL, f_double, del_counting);
    if (mapped == NULL)
        st->passed++;
    else
        st->failed++;

    i1 = malloc(sizeof(*i1));
    i2 = malloc(sizeof(*i2));
    i3 = malloc(sizeof(*i3));
    if (!i1 || !i2 || !i3)
    {
        free(i1); free(i2); free(i3);
        st->failed++;
        return;
    }
    *i1 = 1; *i2 = 2; *i3 = 3;
    n1 = ft_lstnew(i1);
    n2 = ft_lstnew(i2);
    n3 = ft_lstnew(i3);
    if (!n1 || !n2 || !n3)
    {
        free(i1); free(i2); free(i3);
        free(n1); free(n2); free(n3);
        st->failed++;
        return;
    }
    n1->next = n2;
    n2->next = n3;
    list = n1;

    g_del_count = 0;
    mapped = ft_lstmap(list, f_double, del_counting);
    ok = mapped
         && mapped->content
         && ((int *)mapped->content)[0] == 2
         && mapped->next
         && ((int *)mapped->next->content)[0] == 4
         && mapped->next->next
         && ((int *)mapped->next->next->content)[0] == 6
         && mapped->next->next->next == NULL;
    if (ok)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstmap (double): expected [2,4,6], got [%d,%d,%d]\n",
                ((int *)mapped->content)[0],
                ((int *)mapped->next->content)[0],
                ((int *)mapped->next->next->content)[0]);
            fclose(log);
        }
    }
    while (mapped)
    {
        t_list *tmp = mapped->next;
        free(mapped->content);
        free(mapped);
        mapped = tmp;
    }

    g_del_count = 0;
    mapped = ft_lstmap(list, f_fail_on_two, del_counting);
    if (mapped == NULL && g_del_count == 1)
        st->passed++;
    else
    {
        st->failed++;
        log = fopen("error.log", "a");
        if (log)
        {
            fprintf(log,
                "lstmap (fail): expected NULL and del_count=1, got %p and %d\n",
                (void *)mapped, g_del_count);
            fclose(log);
        }
    }

    while (list)
    {
        t_list *tmp = list->next;
        free(list->content);
        free(list);
        list = tmp;
    }
}

