#ifndef MONSTRO_H
#define MONSTRO_H

typedef struct {
    char nome[50];
    int vidaAtual;
    int vidaMax;
    int ataque;
    int defesa;
    int xpDrop;
    int ouroDrop;
} Monstro;

// Função para gerar um monstro básico da Área de Tutorial
void gerarMonstroTutorial(Monstro *m);

#endif