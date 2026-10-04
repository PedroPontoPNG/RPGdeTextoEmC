#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "jogador.h"

void inicializarNovoJogador(Jogador *j, const char *nome) {
    strncpy(j->nome, nome, sizeof(j->nome) - 1);
    j->nome[sizeof(j->nome) - 1] = '\0';

    j->nivel = 1;
    j->xp = 0;
    j->xpProximoNivel = 50;
    j->pontosAtributo = 0;

    j->atributos.vitalidade = 1;
    j->atributos.forca = 1;
    j->atributos.inteligencia = 1;
    j->atributos.agilidade = 1;
    j->atributos.carisma = 1;
    j->atributos.sorte = 1;

    j->status.vidaMax = j->atributos.vitalidade * 10;
    j->status.vidaAtual = j->status.vidaMax;
    j->status.ataque = j->atributos.forca * 2;
    j->status.defesa = j->atributos.agilidade * 1;
    j->status.ouro = 100;
}

typedef struct {
    char nome[50];
    int bonusAtaque;
    int precisao;
    int peso;
} Equipamento;

void exibirStatus(Jogador *j) {
    printf("\n--- STATUS ---\n");
    printf("Nome: %s | Nivel: %d | XP: %d\n", j->nome, j->nivel, j->xp);
    printf("HP: %d/%d | Ataque: %d | Defesa: %d | Ouro: %d\n", 
           j->status.vidaAtual, j->status.vidaMax, j->status.ataque, j->status.defesa, j->status.ouro);
    printf("-----------------------\n");

    printf("Itens equipados:\n Capacete: \n Peitoral: \n Calças: \n Botas:\n");

    printf("\n Acessorios: \n Anel 1: \n Anel 2: \n Brincos: \n Amuleto: \n");

    printf("Vitalidade:%d\nForça:%d\nInteligência:%d\nAgilidade:%d\nCarisma:%d\nSorte:%d",
         j->atributos.vitalidade, j->atributos.forca,  j->atributos.inteligencia, j->atributos.agilidade, 
         j->atributos.carisma, j->atributos.sorte );
    ;
}

int atacar(Jogador *atacante) {
    int dado = (rand() % 20) + 1; // Rola um D20
    int dano_final = atacante->status.ataque;
    
    printf("Voce rolou um %d no dado!\n", dado);
    
    // Abaixo de 5: Erra
    if (dado <= 5) {
        printf("Você ERROU!\n");
        dano_final = 0;
    } 
    // 6 a 9: Acerta com redução de dano
    else if (dado >= 6 && dado <= 9) {
        printf("Ataque de raspão!\n");
        dano_final /= 2; // Corta o dano pela metade
    } 
    // 10 a 15: Acerta com dano total
    else if (dado >= 10 && dado <= 15) {
        printf("Você acertou em cheio!\n");
        // O dano_final se mantém intacto
    } 
    // 16 a 19: Bônus de dano
    else if (dado >= 16 && dado <= 19) {
        printf("Acertou um belo golpe!.\n");
        // Adiciona um bônus que escala com o atributo Força
        dano_final += atacante->atributos.forca; 
    } 
    // 20: Crítico
    else if (dado == 20) {
        printf("ACERTO CRITICO!\n");
        dano_final *= 2; 
    }
    
    return dano_final;
}

// Aumentar Nivel e atributos
void evoluirDeNivel(Jogador *j) {
    if (j->xp >= j->xpProximoNivel) {
        j->nivel++;
        j->xp -= j->xpProximoNivel; // Mantém o XP excedente
        j->xpProximoNivel = (int)(j->xpProximoNivel * 1.5);

        printf("\n*** Subiu de nivel!! ***\n");
        printf("Você alcançou o Nível %d!\n", j->nivel);

        // aumenta a vida máxima
        j->status.vidaMax += 5; 
        j->status.vidaAtual = j->status.vidaMax;

        // Ganha 3 pontos de atributo para ser alocado
        ganharAtributo(j, 3);
    }
}

// Ganha pontos de atributo
void ganharAtributo(Jogador *j, int pontos) {
    j->pontosAtributo += pontos;
    printf("Ganhou %d pontos de atributo!\n", pontos);
    alocar(j);
}

// Alocar atributos
void alocar(Jogador *j) {
    int escolha;

    while (j->pontosAtributo > 0) {
        printf("\n--- ALOCAÇÃO DE ATRIBUTOS ---\n");
        printf("Pontos disponíveis: %d\n", j->pontosAtributo);
        printf("1. Vitalidade (+ HP Máximo)  (Atual: %d)\n", j->atributos.vitalidade);
        printf("2. Força (+ Dano Físico)     (Atual: %d)\n", j->atributos.forca);
        printf("3. Inteligência (+ Mana)     (Atual: %d)\n", j->atributos.inteligencia);
        printf("4. Agilidade (+ Turno)(Atual: %d)\n", j->atributos.agilidade);
        printf("5. Carisma (Comércio/NPCs)   (Atual: %d)\n", j->atributos.carisma);
        printf("6. Sorte (Crítico/Loot)      (Atual: %d)\n", j->atributos.sorte);
        printf("Escolha onde investir 1 ponto: ");
        
        if (scanf("%d", &escolha) != 1) {
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (escolha) {
            case 1: 
                j->atributos.vitalidade++; 
                j->status.vidaMax += 10; // Atualiza a vida
                j->status.vidaAtual += 10;
                break;
            case 2: 
                j->atributos.forca++; 
                j->status.ataque = j->atributos.forca * 2; // Recalcula o ataque base
                break;
            case 3: j->atributos.inteligencia++; break;
            case 4: 
                j->atributos.agilidade++; 
                j->status.defesa = j->atributos.agilidade * 1; // Recalcula a defesa
                break;
            case 5: j->atributos.carisma++; break;
            case 6: j->atributos.sorte++; break;
            default: 
                printf("Opção inválida!\n"); 
                continue; // Volta ao início do loop sem gastar o ponto
        }
        
        j->pontosAtributo--; // Gasta 1 ponto com sucesso
    }
    printf("\nTodos os pontos foram alocados com sucesso!\n");
}


