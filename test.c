#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **ft_get_lines(char *file_name) {
    char    **lines;
    int     fd;

    fd = open(file_name, O_RDONLY);
    
    return (lines);
}

void ft_free_lines(char **lines) {
    for (int i = 0; lines[i] != NULL; i++) {
        free(lines[i]);
    }
    free(lines);
}

int main() {
    char **lines = ft_get_lines("main.c");
    if (lines != NULL) {
        // Utilisez lines ici...

        // Libérez la mémoire lorsque vous avez terminé
        ft_free_lines(lines);
    }

    return 0;
}
