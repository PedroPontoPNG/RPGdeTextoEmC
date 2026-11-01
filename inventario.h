#ifndef INVENTARIO_H
#define INVENTARIO_H

#define INVENTARIO_ESPACOS 30   // quantidade de espaços da bolsa
#define PILHA_MAX          99   // máximo de unidades empilhadas por espaço

// Um espaço guarda só "qual item" e "quantos". Todo o resto (nome, tipo,
// valor...) vem dos catálogos, por isso o save fica pequeno.
// Espaço vazio: id == ITEM_NENHUM (0) e quantidade == 0.
typedef struct {
    int id;          // IdItem
    int quantidade;
} Espaco;

// Os espaços ocupados ficam sempre juntos no início do array (sem buracos),
// então o espaço de número N na tela é espacos[N - 1].
typedef struct {
    Espaco espacos[INVENTARIO_ESPACOS];
} Inventario;

void inicializarInventario(Inventario *inv);

// Adiciona até 'qtd' unidades. Devolve QUANTAS foram adicionadas (0 a qtd);
// se a bolsa encher, o que sobrou não entra.
int adicionarItem(Inventario *inv, int id, int qtd);

// Remove 'qtd' unidades. devolve 1 se removeu, 0 se não havia
// quantidade suficiente (e nesse caso não remove nada).
int removerItem(Inventario *inv, int id, int qtd);

int contarItem(const Inventario *inv, int id);      // total de unidades do item
int espacosLivres(const Inventario *inv);
int espacosUsados(const Inventario *inv);

// 1 se 'qtd' unidades do item cabem inteiras na bolsa
int cabeNoInventario(const Inventario *inv, int id, int qtd);

// Mostra a bolsa na tela. Devolve quantos espaços estão ocupados.
int listarInventario(const Inventario *inv);

// Confere um inventário vindo de um save (IDs e quantidades válidos) e
// arruma buracos entre os espaços. Devolve 1 se está válido, 0 se corrompido.
int validarInventario(Inventario *inv);

#endif
