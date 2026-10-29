#ifndef JOGADOR_H
#define JOGADOR_H

#include "equipamentos.h"

typedef struct {
    int vitalidade;
    int forca;
    int sorte;
    int inteligencia;
    int agilidade;
    int carisma;
} Atributos;

typedef struct {
    int vidaAtual;
    int vidaMax;
    int defesa;
    int ataque;
    int ouro;
} Status;

typedef struct {
    char nome[50];
    int nivel;
    int xp;
    int xpProximoNivel;
    int pontosAtributo;
    Atributos atributos;
    Status status;
    int equipados[SLOT_TOTAL];   // ID (IdItem) de cada slot; ITEM_NENHUM = vazio
} Jogador;

void inicializarNovoJogador(Jogador *j, const char *nome);
void exibirStatus(Jogador *j);
int atacar(Jogador *atacante);

void evoluirDeNivel(Jogador *j);
void ganharAtributo(Jogador *j, int pontos);
void alocar(Jogador *j);

void recalcularStatus(Jogador *j);

// Equipamentos
int equiparItem(Jogador *j, int id);                 // 1 = equipou, 0 = não pôde
int desequiparItem(Jogador *j, SlotEquip slot);      // devolve o ID removido (ITEM_NENHUM se vazio)
int pesoEquipado(const Jogador *j);


#endif