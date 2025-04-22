
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 2
static const char charset[] =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    " ,.;:-_!\"'?/\\|@#$%^&*()[]{}<>+=";

static char buffer[MAX_LEN + 1];

/* Recursivamente genera todas las cadenas de longitud <= MAX_LEN */
void gen_cases(int pos, FILE *f)
{
    /* Siempre imprimimos el caso actual (incluyendo la cadena vacía al comienzo) */
    buffer[pos] = '\0';
    for (int c = 0; c <= 255; c++)
        fprintf(f, "strrchr:%s,%d\n", buffer, c);

    /* Si aún podemos añadir más caracteres, iteramos sobre el charset */
    if (pos == MAX_LEN)
        return;
    for (size_t i = 0; i < sizeof(charset) - 1; i++)
    {
        buffer[pos] = charset[i];
        gen_cases(pos + 1, f);
    }
}

int main(void)
{
    FILE *f = fopen("ft_strrchr_tests.txt", "w");
    if (!f)
    {
        perror("fopen");
        return EXIT_FAILURE;
    }

    /* Arranca la generación con posición 0 */
    gen_cases(0, f);

    fclose(f);
    return EXIT_SUCCESS;
}
