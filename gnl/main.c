//#include "get_next_line.h"
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*is_the_longest_line(char *str)
{
	static char	*string_stock;
	char		*temp_string_stock;

	if (!string_stock)
	{
		string_stock = strdup(str);
		return (string_stock);
	}
		
	if (strlen(str) > strlen(string_stock))
	{
		temp_string_stock = string_stock;
		string_stock = strdup(str);
		free(temp_string_stock);
		return (string_stock);
	}
	else
		return (string_stock);
}

int	main(int argc, char **argv)
{
	int		fd1;
	FILE	*temp_file;
	char	*string;
	char	filepath[256];
	char	cmd[512];
	int		i;

	if (argc < 2)
	{
		printf("Pero amiguito,¿no hemos aprendido nada? es ./a.out <nombre_del_archivo_de_test>\n");
		return (0);
	}
	i = 1;
	if (strncmp(argv[i], "bonus.txt", strlen("bonus.txt")))
	{
		while (i < argc)
		{
			printf("\n=== Procesando: %s ===\n", argv[i]);
			if (!strncmp(argv[i], "stdin.txt", strlen("stdin.txt")))
			{
				printf("Estoy en stdin lisa!\n");
				fd1 = 0;
			}
			else
			{
				snprintf(filepath, sizeof(filepath), "test/%s", argv[i]);
				fd1 = open(filepath, O_RDONLY);
				if (fd1 < 0)
				{
					printf("Error: No se pudo abrir %s\n", filepath);
					i++;
					continue ;
				}
			}
			if (!strncmp(argv[i], "no_fd.txt", strlen("no_fd.txt")))
				close(fd1);
			temp_file = fopen("temp_output.txt", "w");
			if (!temp_file)
			{
				printf("Error: No se pudo crear temp_output.txt\n");
				close(fd1);
				i++;
				continue ;
			}
			while ((string = get_next_line(fd1)) != NULL)
			{
				printf("\033[33m%s\033[0m", string);
				fprintf(temp_file, "%s", string);
				free(string);
			}
			fclose(temp_file);
			if (fd1 >= 0)
				close(fd1);
			if (strncmp(argv[i], "stdin.txt", strlen("stdin.txt")))
			{
				snprintf(cmd, sizeof(cmd), "diff -q temp_output.txt test/%s",argv[i]);
				if (system(cmd) == 0)
					printf("\033[33m\n✓ Test PASADO: %s\n\033[0m", argv[i]);
				else
				{
					printf("\033[33m\n✗ Test FALLIDO: %s- Diferencias:\n\033[0m", argv[i]);
					snprintf(cmd, sizeof(cmd), "diff temp_output.txt test/%s", argv[i]);
					system(cmd);
				}
			}
			i++;
		}
	remove("temp_output.txt");	
	}
else
{
    char *filenames[] = {"tolkien.txt", "el_quijote.txt", "hegel.txt", "fiodor.txt"};
    int file_descriptors[4];
    int num_files = 4;
    int active_files = num_files;
    
    for (int i = 0; i < num_files; i++)
    {
        snprintf(filepath, sizeof(filepath), "test/%s", filenames[i]);
        file_descriptors[i] = open(filepath, O_RDONLY);
        
        if (file_descriptors[i] < 0)
        {
            printf("Error: No se pudo abrir %s\n", filepath);
            file_descriptors[i] = -1;
        }
    }
    
    while (active_files > 0)
    {
        for (int i = 0; i < num_files; i++)
        {
            if (file_descriptors[i] >= 0)
            {
                string = get_next_line(file_descriptors[i]);
                
                if (string != NULL)
                {
                    printf("[%s]: %s", filenames[i], string);
                    is_the_longest_line(string);
                    free(string);
                }
                else
                {
                    close(file_descriptors[i]);
                    file_descriptors[i] = -1;
                    active_files--;
                    printf("[%s]: <archivo terminado>\n", filenames[i]);
                }
            }
        }
    }
    
    char *longest = is_the_longest_line("");
    printf("\nla linea más larga del universo universal es \n\n %s \n\n ¿No es genial?\n", 
           longest);
	free(longest);
}
return (0);
	return (0);
}
