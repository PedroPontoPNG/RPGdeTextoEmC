#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "jogador.h"
#include "funcSistema.h"
#include "cidades.h"
#include "entrada.h"

int main() {
    srand(time(NULL));
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    Jogador player1 = {0};
    EstadoJogo estadoAtual = ESTADO_MENU_INICIAL;
    int opcaoMenu = -1;
    char nomeHeroi[50];

    while (estadoAtual != ESTADO_SAIR) {
        switch (estadoAtual) {
            case ESTADO_MENU_INICIAL:
                printf("\n====== RPG DE TEXTO ======\n");
                printf("1. Novo Jogo\n");
                printf("2. Carregar Jogo\n");
                printf("3. Salvar Jogo\n");
                printf("0. Sair do Jogo\n");
                printf("==========================\n");
                opcaoMenu = lerInt("Escolha: ");

                if (opcaoMenu == 1) {
                    printf("Digite o nome do herói: ");
                    if (fgets(nomeHeroi, sizeof(nomeHeroi), stdin) == NULL) nomeHeroi[0] = '\0';
                    nomeHeroi[strcspn(nomeHeroi, "\n")] = 0;
                    if (nomeHeroi[0] == '\0') strcpy(nomeHeroi, "Heroi");

                    inicializarNovoJogador(&player1, nomeHeroi);
                    estadoAtual = ESTADO_CIDADE;
                } else if (opcaoMenu == 2) {
                    if (carregarJogo(&player1, ARQUIVO_SAVE)) {
                        printf("Jogo carregado! Bem-vindo de volta, %s.\n", player1.nome);
                        estadoAtual = ESTADO_CIDADE;
                    } else {
                        printf("Nenhum save válido encontrado.\n");
                    }
                } else if (opcaoMenu == 3) {
                    if (player1.nivel > 0) {
                        salvarJogo(&player1, ARQUIVO_SAVE);
                    } else {
                        printf("Crie um personagem antes de salvar!\n");
                    }
                } else if (opcaoMenu == 0) {
                    estadoAtual = ESTADO_SAIR;
                } else {
                    printf("Opção inválida!\n");
                }
                break;

            case ESTADO_CIDADE:
                estadoAtual = rodarMenuCidade(&player1);
                break;

            case ESTADO_FLORESTA:
                printf("\nVocê adentra a floresta escura...\n");
                Monstro inimigo;
                gerarMonstroTutorial(&inimigo);
                iniciarCombate(&player1, &inimigo);
                estadoAtual = ESTADO_CIDADE;
                break;

            default:
                estadoAtual = ESTADO_SAIR;
                break;
        }
    }

    printf("\nObrigado por jogar!\n");
    return 0;
}