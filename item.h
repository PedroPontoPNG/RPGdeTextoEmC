#ifndef ITEM_H
#define ITEM_H

#include "equipamentos.h"   // enum IdItem (os IDs de TODOS os itens ficam lá)

// Catálogo geral: dados comuns a qualquer item, seja ele do tipo que for.
//
// Equipamentos continuam descritos só em equipamentos.c (slot, ataque,
// defesa...). Para eles, nome e valor vêm de lá, então não há dado duplicado.
// Consumíveis, materiais e itens de missão são descritos na tabela de item.c.
//
// Todas as funções aceitam qualquer ID. Para um ID inválido devolvem valores
// neutros ("?", "", 0). Use itemValido() quando precisar saber se o ID existe.

typedef enum {
    TIPO_CONSUMIVEL,
    TIPO_MATERIAL,
    TIPO_MISSAO,
    TIPO_EQUIPAMENTO
} TipoItem;

int         itemValido(int id);          // 1 se o ID corresponde a um item real
TipoItem    tipoItem(int id);            // só tem sentido para IDs válidos
const char *nomeTipo(TipoItem tipo);     // ex.: "Consumível"

const char *nomeItem(int id);
const char *descricaoItem(int id);       // "" se o item não tem descrição
int         valorItem(int id);           // valor base de compra/venda
int         itemEmpilha(int id);         // 1 = vários itens no mesmo espaço
int         curaItem(int id);            // HP restaurado ao usar (0 = não cura)

#endif
