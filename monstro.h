#ifndef MONSTRO_H
#define MONSTRO_H

// Struct e info dos monstros
typedef struct {
    char nome[50];
    int vidaAtual;
    int vidaMax;
    int ataque;
    int defesa;
    int xpDrop;
    int ouroDrop;
} Monstro;

// Áreas do jogo
// Adicionar outras antes de AREA_TOTAL
typedef enum {
    AREA_FLORESTA,
    AREA_TOTAL
} AreaJogo;

// Sorteia um monstro da tabela da área e rola seus atributos aleatórios
void gerarMonstroAleatorio(Monstro *m, AreaJogo area);

#endif