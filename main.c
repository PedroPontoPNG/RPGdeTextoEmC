#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "jogador.h"
#include "funcSistema.h"
#include "cidades.h"

int main() {
    srand(time(NULL));
    system("chcp 65001 > nul");
    Jogador player1 = {0};
    const char *arquivoSave = "savegame.dat";

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
                printf("Escolha: ");
                scanf("%d", &opcaoMenu);
                getchar();

                if (opcaoMenu == 1) {
                    printf("Digite o nome do herói: ");
                    fgets(nomeHeroi, sizeof(nomeHeroi), stdin);
                    nomeHeroi[strcspn(nomeHeroi, "\n")] = 0;
                    
                    inicializarNovoJogador(&player1, nomeHeroi);
                    estadoAtual = ESTADO_CIDADE; 
                } else if (opcaoMenu == 2) {
                    if (carregarJogo(&player1, arquivoSave)) {
                        printf("Jogo carregado! Bem-vindo de volta, %s.\n", player1.nome);
                        estadoAtual = ESTADO_CIDADE;
                    } else {
                        printf("Nenhum save encontrado.\n");
                    }
                } else if (opcaoMenu == 3) {
                    if (player1.nivel > 0) {
                        salvarJogo(&player1, arquivoSave);
                    } else {
                        printf("Crie um personagem antes de salvar!\n");
                    }
                } else if (opcaoMenu == 0) {
                    estadoAtual = ESTADO_SAIR;
                }
                break;

            case ESTADO_CIDADE:
                estadoAtual = rodarMenuCidade(&player1);
                break;

            case ESTADO_FLORESTA:
                printf("\nVocê adentra a floresta escura...\n");
                
                Monstro inimigo;
                gerarMonstroTutorial(&inimigo); // Cria o monstro
                
                iniciarCombate(&player1, &inimigo); // Inicia a luta
                
                // Depois que o combate acaba (vitória ou fuga), o jogador volta à cidade
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