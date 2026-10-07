#include <stdio.h>
#include "cidades.h"
#include "entrada.h"

EstadoJogo rodarMenuCidade(Jogador *j) {
    int opcao = -1;

    while (1) {
        printf("\n====================================\n");
        printf("       CIDADE 1           \n");
        printf("====================================\n");
        printf("1. Visitar a Taverna (Descansar / Curar)\n");
        printf("2. Visitar a Loja de Armas e Armaduras\n");
        printf("3. Exibir Status do Personagem\n");
        printf("4. Ir para a Floresta\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("====================================\n");
        printf("Escolha sua ação: ");

        opcao = lerInt("Escolha sua ação: ");

        switch (opcao) {
            case 1:
                visitarTaverna(j);
                break;
            case 2:
                visitarLoja(j);
                break;
            case 3:
                exibirStatus(j);
                break;
            case 4:
                printf("\nVocê pega seu equipamento e atravessa os grandes portões em direção à floresta...\n");
                return ESTADO_FLORESTA; // Muda o estado para a Floresta
            case 0:
                printf("\nSaindo para o menu principal...\n");
                return ESTADO_MENU_INICIAL;
            default:
                printf("\nOpção inválida!\n");
        }
    }
}

void visitarTaverna(Jogador *j) {
    int custo = 10;
    
    printf("\n--- TAVERNA ---\n");
    printf("O taverneiro diz: 'Bem-vindo! Um quarto para passar a noite custa %d moedas de ouro.'\n", custo);
    
    if (j->status.vidaAtual == j->status.vidaMax) {
        printf("Você não precisa descansar agora.\n");
        return;
    }

    if (j->status.ouro >= custo) {
        j->status.ouro -= custo;
        j->status.vidaAtual = j->status.vidaMax;
        printf("Você dormiu uma boa noite de sono. Sua vida foi restaurada! (HP: %d/%d)\n", 
               j->status.vidaAtual, j->status.vidaMax);
        printf("Ouro restante: %d\n", j->status.ouro);
    } else {
        printf("Você não tem ouro suficiente! Volte quando tiver pelo menos %d moedas.\n", custo);
    }
}

void visitarLoja(Jogador *j) {
    (void)j;  
    printf("\nO ferreiro ainda está arrumando a oficina. Volte em breve\n");
}