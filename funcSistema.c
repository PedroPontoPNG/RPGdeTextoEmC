#include <stdio.h>
#include "funcSistema.h"
#include "jogador.h"
#include "entrada.h"

void salvarJogo(Jogador *j, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de save!\n");
        return;
    }
    int versao = SAVE_VERSAO;
    fwrite(&versao, sizeof versao, 1, arquivo);
    fwrite(j, sizeof(Jogador), 1, arquivo);
    fclose(arquivo);
    printf("Jogo salvo com sucesso!\n");
}

int carregarJogo(Jogador *j, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        return 0;
    }

    int versao;
    Jogador tmp;
    if (fread(&versao, sizeof versao, 1, arquivo) != 1 ||
        versao != SAVE_VERSAO ||
        fread(&tmp, sizeof(Jogador), 1, arquivo) != 1) {
        fclose(arquivo);
        return 0;
    }
fclose(arquivo);
    *j = tmp;
    recalcularStatus(j);   // reaplica os bônus da tabela de itens
    return 1;
}

void iniciarCombate(Jogador *j, Monstro *m) {
    printf("\nUm %s selvagem apareceu!\n", m->nome);

    while (j->status.vidaAtual > 0 && m->vidaAtual > 0) {
        printf("\n--- TURNO DO JOGADOR ---\n");
        printf("Seu HP: %d/%d | HP do %s: %d/%d\n",
               j->status.vidaAtual, j->status.vidaMax, m->nome, m->vidaAtual, m->vidaMax);
        printf("1. Atacar\n");
        printf("2. Fugir\n");

        int acao = lerInt("Escolha: ");

        if (acao == 1) {
            int dano = atacar(j);
            if (dano > 0) {
                // Calcula o dano reduzindo a defesa do monstro
                int danoFinal = dano - m->defesa;
                if (danoFinal < 0) danoFinal = 0; // Impede que a defesa cure o monstro
                printf("Voce causou %d de dano (A defesa absorveu %d).\n", danoFinal, m->defesa);
                m->vidaAtual -= danoFinal;
            }

            // Verifica se o monstro morreu
            if (m->vidaAtual <= 0) {
                printf("\nVoce derrotou o %s!\n", m->nome);
                printf("Recebeu %d XP e %d moedas de ouro.\n", m->xpDrop, m->ouroDrop);
                j->xp += m->xpDrop;
                j->status.ouro += m->ouroDrop;
                evoluirDeNivel(j);
                salvarJogo(j, ARQUIVO_SAVE);
                break;
            }

            // --- TURNO DO MONSTRO ---
            printf("\n--- TURNO DO INIMIGO ---\n");
            int danoMonstro = m->ataque - j->status.defesa;
            if (danoMonstro < 0) danoMonstro = 0;

            printf("O %s atacou e causou %d de dano!\n", m->nome, danoMonstro);
            j->status.vidaAtual -= danoMonstro;

            if (j->status.vidaAtual <= 0) {
                int perda = j->status.ouro / 10;   // resgate custa 10% do ouro
                j->status.ouro -= perda;
                j->status.vidaAtual = j->status.vidaMax / 2;
                if (j->status.vidaAtual < 1) j->status.vidaAtual = 1;

                printf("\nVoce caiu em combate...\n");
                printf("Mas os soldados ouviram seus gritos e lhe resgataram a tempo.\n");
                printf("O resgate custou %d de ouro. HP: %d/%d\n",
                       perda, j->status.vidaAtual, j->status.vidaMax);
                break;
            }
        } else if (acao == 2) {
            printf("\nVoce foge...\n");
            break;
        } else {
            printf("Acao invalida!\n");
        }
    }
}