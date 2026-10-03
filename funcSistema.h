#ifndef FUNCSISTEMA_H
#define FUNCSISTEMA_H

#include "jogador.h"
#include "monstro.h"

void salvarJogo(Jogador *j, const char *nomeArquivo);
int carregarJogo(Jogador *j, const char *nomeArquivo);

void iniciarCombate(Jogador *j, Monstro *m);

#endif