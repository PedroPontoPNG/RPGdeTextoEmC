#ifndef FUNCSISTEMA_H
#define FUNCSISTEMA_H

#include "jogador.h"
#include "monstro.h"

#define ARQUIVO_SAVE "savegame.dat"
#define SAVE_VERSAO  3   // 3: inventário dentro de Jogador

void salvarJogo(Jogador *j, const char *nomeArquivo);
int carregarJogo(Jogador *j, const char *nomeArquivo);

void iniciarCombate(Jogador *j, Monstro *m);


#endif