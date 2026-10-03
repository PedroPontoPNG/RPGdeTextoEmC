#ifndef JOGADOR_H
#define JOGADOR_H

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
} Jogador;

void inicializarNovoJogador(Jogador *j, const char *nome);
void exibirStatus(Jogador *j);
int atacar(Jogador *atacante);

void evoluirDeNivel(Jogador *j);
void ganharAtributo(Jogador *j, int pontos);
void alocar(Jogador *j);


#endif