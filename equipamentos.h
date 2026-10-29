#ifndef EQUIPAMENTOS_H
#define EQUIPAMENTOS_H

// Slots onde um item pode ser equipado.
// Para um novo slot, adicione antes de SLOT_TOTAL.
// Obs. o item "anel" pode ser equipado tanto no SLOT_ANEL1, quanto no SLOT_ANEL2
typedef enum {
    SLOT_ARMA,
    SLOT_CAPACETE,
    SLOT_PEITORAL,
    SLOT_CALCAS,
    SLOT_BOTAS,
    SLOT_ANEL1,
    SLOT_ANEL2,
    SLOT_BRINCOS,
    SLOT_AMULETO,
    SLOT_TOTAL
} SlotEquip;

// IDs dos itens
// REGRAS: não reordenar nem remova IDs existentes, senão saves antigos
// passam a apontar para o item errado. 
// Item novo entra SEMPRE antes de ITEM_TOTAL.
// ITEM_NENHUM (0) significa "slot vazio".
typedef enum {
    ITEM_NENHUM = 0,
    ITEM_ADAGA_ENFERRUJADA,
    ITEM_ESPADA_CURTA,
    ITEM_MACHADO_DE_GUERRA,
    ITEM_CAPACETE_COURO,
    ITEM_PEITORAL_COURO,
    ITEM_PEITORAL_FERRO,
    ITEM_CALCAS_COURO,
    ITEM_BOTAS_COURO,
    ITEM_ANEL_BRONZE,
    ITEM_BRINCOS_PRATA,
    ITEM_AMULETO_OSSO,
    ITEM_TOTAL
} IdItem;

// Dados fixos de um item (ficam na tabela, não no save)
typedef struct {
    const char *nome;
    SlotEquip slot;
    int ataque;        // bônus somado ao ataque do jogador
    int defesa;        // bônus somado à defesa do jogador
    int peso;          // Ainda sem uso
    int valor;         // valor base de compra/venda
    int forcaMin;      // status mínimo para equipar (0 = sem exigência)
    int agilidadeMin;
} Equipamento;

// Devolve os dados do item, ou NULL se o ID for ITEM_NENHUM ou inválido
const Equipamento *obterItem(int id);

// Nome de exibição do slot (ex.: "Capacete")
const char *nomeSlot(SlotEquip slot);

#endif
