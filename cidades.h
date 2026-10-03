#ifndef CIDADE_H
#define CIDADE_H

#include "jogador.h"

typedef enum {
    ESTADO_MENU_INICIAL,
    ESTADO_CIDADE,
    ESTADO_FLORESTA,
    ESTADO_SAIR
} EstadoJogo;

EstadoJogo rodarMenuCidade(Jogador *j);

void visitarTaverna(Jogador *j);
void visitarLoja(Jogador *j);

#endif