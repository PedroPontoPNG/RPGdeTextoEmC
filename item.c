#include <stddef.h>
#include "item.h"

// Descrição de um item que NÃO é equipamento.
typedef struct {
    const char *nome;        // NULL = linha vazia (ID sem item)
    TipoItem tipo;
    const char *descricao;
    int valor;               // valor base de compra/venda
    int empilha;             // 1 = empilha até PILHA_MAX por espaço
    int cura;                // HP restaurado ao usar (só consumíveis)
} InfoItem;

// CATÁLOGO
// O índice da tabela é o próprio ID (enum IdItem em equipamentos.h), então
// a ordem aqui não importa. Equipamentos não entram aqui, ficam em equipamentos.c.
// Para um item novo: 1) adicione o ID no enum, 2) adicione a linha aqui.
static const InfoItem catalogo[ITEM_TOTAL] = {
    // Consumíveis
    [ITEM_POCAO_CURA_PEQUENA] = { "Poção de Cura Pequena", TIPO_CONSUMIVEL,
                                  "Um frasco de liquido vermelho. Restaura 30 de vida.",
                                  20, 1, 30 },
    [ITEM_ERVA_MEDICINAL]     = { "Erva Medicinal", TIPO_CONSUMIVEL,
                                  "Mastigada, restaura 10 de vida.",
                                  5, 1, 10 },

    // Materiais
    [ITEM_COURO_LOBO]         = { "Couro de Lobo", TIPO_MATERIAL,
                                  "Couro resistente, útil para criar roupas e equipamentos basicos.",
                                  8, 1, 0 },
    [ITEM_MINERIO_FERRO]      = { "Minério de Ferro", TIPO_MATERIAL,
                                  "Minério bruto de ferro que pode ser fundido na forja.",
                                  12, 1, 0 },

    // Itens de missão (não empilham)
    [ITEM_CHAVE_ENFERRUJADA]  = { "Chave Enferrujada", TIPO_MISSAO,
                                  "Uma chave antiga. Deve abrir algo importante.",
                                  0, 0, 0 },
};

// Linha do catálogo, ou NULL se o ID não for um item não-equipamento.
static const InfoItem *buscarInfo(int id) {
    if (id <= ITEM_NENHUM || id >= ITEM_TOTAL) return NULL;
    if (catalogo[id].nome == NULL) return NULL;
    return &catalogo[id];
}

int itemValido(int id) {
    return obterItem(id) != NULL || buscarInfo(id) != NULL;
}

TipoItem tipoItem(int id) {
    if (obterItem(id) != NULL) return TIPO_EQUIPAMENTO;
    const InfoItem *info = buscarInfo(id);
    return info ? info->tipo : TIPO_MATERIAL;
}

const char *nomeTipo(TipoItem tipo) {
    switch (tipo) {
        case TIPO_CONSUMIVEL:  return "Consumível";
        case TIPO_MATERIAL:    return "Material";
        case TIPO_MISSAO:      return "Missão";
        case TIPO_EQUIPAMENTO: return "Equipamento";
    }
    return "?";
}

const char *nomeItem(int id) {
    const Equipamento *eq = obterItem(id);
    if (eq != NULL) return eq->nome;
    const InfoItem *info = buscarInfo(id);
    return info ? info->nome : "?";
}

const char *descricaoItem(int id) {
    const InfoItem *info = buscarInfo(id);
    return info ? info->descricao : "";
}

int valorItem(int id) {
    const Equipamento *eq = obterItem(id);
    if (eq != NULL) return eq->valor;
    const InfoItem *info = buscarInfo(id);
    return info ? info->valor : 0;
}

int itemEmpilha(int id) {
    const InfoItem *info = buscarInfo(id);   // equipamentos nunca empilham
    return info ? info->empilha : 0;
}

int curaItem(int id) {
    const InfoItem *info = buscarInfo(id);
    return info ? info->cura : 0;
}
