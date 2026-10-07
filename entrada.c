#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"

int lerInt(const char *prompt) {
    char buf[32];
    printf("%s", prompt);

    if (fgets(buf, sizeof buf, stdin) == NULL) return -1;

    // Linha maior que o buffer: descarta o resto para não vazar no próximo menu
    if (strchr(buf, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    char *fim;
    long v = strtol(buf, &fim, 10);
    if (fim == buf) return -1;   // nenhum digito lido
    return (int)v;
}