#include <stdio.h>
#include "funcSistema.h"
#include "jogador.h"

void salvarJogo(Jogador *j, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de save!\n");
        return;
    }

    fwrite(j, sizeof(Jogador), 1, arquivo);
    fclose(arquivo);
    printf("Jogo salvo com sucesso!\n");
}

int carregarJogo(Jogador *j, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    
    if (arquivo == NULL) {
        return 0; 
    }
    
    fread(j, sizeof(Jogador), 1, arquivo);
    fclose(arquivo);
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
        printf("Escolha: ");
        
        int acao = -1;
        if (scanf("%d", &acao) != 1) {
            while (getchar() != '\n');
            continue;
        }
        getchar();

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
                salvarJogo(j, "savegame.dat");
                break; // Sai do loop de combate
            }

            // --- TURNO DO MONSTRO ---
            printf("\n--- TURNO DO INIMIGO ---\n");
            int danoMonstro = m->ataque - j->status.defesa;
            if (danoMonstro < 0) danoMonstro = 0;
            
            printf("O %s atacou e causou %d de dano!\n", m->nome, danoMonstro);
            j->status.vidaAtual -= danoMonstro;

            if (j->status.vidaAtual <= 0) {
                printf("\nVoce caiu em combate...\n");
                printf("Mas os solados ouviram seus gritos e lhe resgataram a tempo\n")
                break;
            }
        } else if (acao == 2) {
            printf("\nVoce foge...\n");
            break; // Sai do combate
            salvarJogo(j, "savegame.dat");
        } else {
            printf("Acao invalida!\n");
        }
    }

    
}