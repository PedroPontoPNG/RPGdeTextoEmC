#include <stddef.h>
#include "equipamentos.h"

// TABELA DE ITENS
// O indice da tabela é o próprio ID,a ordem aqui não importa
// (os IDs vêm do enum em equipamentos.h).
//                                nome                  slot          atq def peso valor  forMin agiMin
static const Equipamento tabelaItens[ITEM_TOTAL] = {
    [ITEM_ADAGA_ENFERRUJADA] = { "Adaga Enferrujada",   SLOT_ARMA,     1,  0,  1,   10,    0,     0 },
    [ITEM_ESPADA_CURTA]      = { "Espada Curta",        SLOT_ARMA,     3,  0,  3,   40,    3,     0 },
    [ITEM_MACHADO_DE_GUERRA] = { "Machado de Guerra",   SLOT_ARMA,     6,  0,  8,  120,    6,     0 },

    [ITEM_CAPACETE_COURO]    = { "Capacete de Couro",   SLOT_CAPACETE, 0,  1,  1,   15,    0,     0 },
    [ITEM_PEITORAL_COURO]    = { "Peitoral de Couro",   SLOT_PEITORAL, 0,  2,  4,   30,    0,     0 },
    [ITEM_PEITORAL_FERRO]    = { "Peitoral de Ferro",   SLOT_PEITORAL, 0,  4, 10,   90,    4,     0 },
    [ITEM_CALCAS_COURO]      = { "Calças de Couro",     SLOT_CALCAS,   0,  1,  2,   20,    0,     0 },
    [ITEM_BOTAS_COURO]       = { "Botas de Couro",      SLOT_BOTAS,    0,  1,  1,   15,    0,     0 },

    [ITEM_ANEL_BRONZE]       = { "Anel de Bronze",      SLOT_ANEL1,    1,  0,  0,   25,    0,     0 },
    [ITEM_BRINCOS_PRATA]     = { "Brincos de Prata",    SLOT_BRINCOS,  0,  1,  0,   25,    0,     0 },
    [ITEM_AMULETO_OSSO]      = { "Amuleto de Osso",     SLOT_AMULETO,  1,  1,  1,   50,    0,     0 },
};

static const char *nomesSlots[SLOT_TOTAL] = {
    [SLOT_ARMA]     = "Arma",
    [SLOT_CAPACETE] = "Capacete",
    [SLOT_PEITORAL] = "Peitoral",
    [SLOT_CALCAS]   = "Calças",
    [SLOT_BOTAS]    = "Botas",
    [SLOT_ANEL1]    = "Anel 1",
    [SLOT_ANEL2]    = "Anel 2",
    [SLOT_BRINCOS]  = "Brincos",
    [SLOT_AMULETO]  = "Amuleto",
};

const Equipamento *obterItem(int id) {
    if (id <= ITEM_NENHUM || id >= ITEM_TOTAL) return NULL;
    return &tabelaItens[id];
}

const char *nomeSlot(SlotEquip slot) {
    if (slot < 0 || slot >= SLOT_TOTAL) return "?";
    return nomesSlots[slot];
}
