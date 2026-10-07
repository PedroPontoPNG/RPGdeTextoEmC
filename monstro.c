#include <string.h>
#include "monstro.h"

void gerarMonstroTutorial(Monstro *m) {
    strncpy(m->nome, "Goblin da Floresta", sizeof(m->nome) - 1);
    m->nome[sizeof(m->nome) - 1] = '\0';
    m->vidaMax = 8;
    m->vidaAtual = m->vidaMax;
    m->ataque = 2;
    m->defesa = 0;
    m->xpDrop = 15;
    m->ouroDrop = 5;
}