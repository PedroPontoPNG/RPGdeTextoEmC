#include <string.h>
#include "monstro.h"

void gerarMonstroTutorial(Monstro *m) {
    strncpy(m->nome, "Goblin da Floresta", sizeof(m->nome) - 1);
    m->nome[sizeof(m->nome) - 1] = '\0';
    
    m->vidaMax = 15;
    m->vidaAtual = m->vidaMax;
    m->ataque = 3;
    m->defesa = 1;
    m->xpDrop = 15;
    m->ouroDrop = 5;
}