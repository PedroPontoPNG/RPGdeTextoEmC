#include <stdlib.h>
#include <string.h>
#include "monstro.h"

#define TAMANHO_ARRAY(a) (sizeof(a) / sizeof((a)[0]))

// Modelo: descreve os LIMITES de um tipo de monstro.
// Cada monstro gerado sorteia seus atributos dentro desses limites.
typedef struct {
    const char *nome;
    int vidaMin,  vidaMax;
    int ataqueMin, ataqueMax;
    int defesaMin, defesaMax;
    int xpMin,    xpMax;
    int ouroMin,  ouroMax;
    int peso;   // chance de aparecer (maior = mais comum)
} ModeloMonstro;

// Uma tabela = um array de modelos + quantos itens ele tem
typedef struct {
    const ModeloMonstro *modelos;
    int quantidade;
} TabelaArea;

// TABELAS DE MONSTROS

//nome                              vida       atq     def     xp       ouro   peso
static const ModeloMonstro tabelaFloresta[] = {
    { "Goblin da Floresta",         8, 14,    1, 3,   0, 2,   5, 9,    3,  8,   50 },
    { "Lobo Selvagem",              10, 16,   2, 4,   1, 2,   6, 11,   2,  6,   30 },
    { "coelho monstro",             6, 12,    1, 3,   0, 1,   2, 8,    4, 10,   15 },
    { "Ent pequeno",                18, 26,   2, 4,   3, 5,   35, 50,  10, 20,  5 },
};

// Liga cada área à sua tabela. Para uma nova área:
//   1) crie a tabela acima, 2) adicione no enum AreaJogo, 3) adicione aqui.
static const TabelaArea tabelasPorArea[AREA_TOTAL] = {
    [AREA_FLORESTA] = { tabelaFloresta, (int)TAMANHO_ARRAY(tabelaFloresta) },
};

// - Funções auxiliares -

// Número inteiro aleatório entre min e max
static int aleatorioEntre(int min, int max) {
    if (max <= min) return min;
    return min + rand() % (max - min + 1);
}

// Sorteia um modelo da tabela
static const ModeloMonstro *sortearModelo(const TabelaArea *tabela) {
    int pesoTotal = 0;
    for (int i = 0; i < tabela->quantidade; i++) {
        pesoTotal += tabela->modelos[i].peso;
    }

    int sorteio = rand() % pesoTotal;
    for (int i = 0; i < tabela->quantidade; i++) {
        if (sorteio < tabela->modelos[i].peso) {
            return &tabela->modelos[i];
        }
        sorteio -= tabela->modelos[i].peso;
    }
    return &tabela->modelos[0]; // não deveria chegar aqui 
}

void gerarMonstroAleatorio(Monstro *m, AreaJogo area) {
    const TabelaArea *tabela = &tabelasPorArea[area];
    const ModeloMonstro *modelo = sortearModelo(tabela);

    strncpy(m->nome, modelo->nome, sizeof(m->nome) - 1);
    m->nome[sizeof(m->nome) - 1] = '\0';

    m->vidaMax   = aleatorioEntre(modelo->vidaMin,   modelo->vidaMax);
    m->vidaAtual = m->vidaMax;
    m->ataque    = aleatorioEntre(modelo->ataqueMin, modelo->ataqueMax);
    m->defesa    = aleatorioEntre(modelo->defesaMin, modelo->defesaMax);
    m->xpDrop    = aleatorioEntre(modelo->xpMin,     modelo->xpMax);
    m->ouroDrop  = aleatorioEntre(modelo->ouroMin,   modelo->ouroMax);
}