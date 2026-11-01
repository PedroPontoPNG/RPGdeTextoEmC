#include <stdio.h>
#include <string.h>
#include "inventario.h"
#include "item.h"

// Junta os espaços ocupados no início do array, mantendo a ordem.
static void compactar(Inventario *inv) {
    int w = 0;
    for (int r = 0; r < INVENTARIO_ESPACOS; r++) {
        if (inv->espacos[r].id != ITEM_NENHUM && inv->espacos[r].quantidade > 0) {
            if (w != r) inv->espacos[w] = inv->espacos[r];
            w++;
        }
    }
    for (; w < INVENTARIO_ESPACOS; w++) {
        inv->espacos[w].id = ITEM_NENHUM;
        inv->espacos[w].quantidade = 0;
    }
}

// Quantas unidades do item ainda cabem na bolsa.
static int capacidadeRestante(const Inventario *inv, int id) {
    int livres = espacosLivres(inv);
    if (!itemEmpilha(id)) return livres;   // 1 unidade por espaço

    int cap = livres * PILHA_MAX;
    for (int i = 0; i < INVENTARIO_ESPACOS; i++) {
        if (inv->espacos[i].id == id) cap += PILHA_MAX - inv->espacos[i].quantidade;
    }
    return cap;
}

void inicializarInventario(Inventario *inv) {
    memset(inv, 0, sizeof *inv);   // ITEM_NENHUM == 0 e quantidade 0 = vazio
}

int espacosUsados(const Inventario *inv) {
    int n = 0;
    for (int i = 0; i < INVENTARIO_ESPACOS; i++) {
        if (inv->espacos[i].id != ITEM_NENHUM) n++;
    }
    return n;
}

int espacosLivres(const Inventario *inv) {
    return INVENTARIO_ESPACOS - espacosUsados(inv);
}

int contarItem(const Inventario *inv, int id) {
    if (id == ITEM_NENHUM) return 0;
    int total = 0;
    for (int i = 0; i < INVENTARIO_ESPACOS; i++) {
        if (inv->espacos[i].id == id) total += inv->espacos[i].quantidade;
    }
    return total;
}

int cabeNoInventario(const Inventario *inv, int id, int qtd) {
    if (!itemValido(id) || qtd <= 0) return 0;
    return qtd <= capacidadeRestante(inv, id);
}

int adicionarItem(Inventario *inv, int id, int qtd) {
    if (!itemValido(id) || qtd <= 0) return 0;

    int restante = qtd;

    // 1) completa as pilhas que já existem
    if (itemEmpilha(id)) {
        for (int i = 0; i < INVENTARIO_ESPACOS && restante > 0; i++) {
            if (inv->espacos[i].id != id) continue;
            int cabe = PILHA_MAX - inv->espacos[i].quantidade;
            int poe = restante < cabe ? restante : cabe;
            inv->espacos[i].quantidade += poe;
            restante -= poe;
        }
    }

    // 2) o que sobrou vai para espaços vazios
    int porEspaco = itemEmpilha(id) ? PILHA_MAX : 1;
    for (int i = 0; i < INVENTARIO_ESPACOS && restante > 0; i++) {
        if (inv->espacos[i].id != ITEM_NENHUM) continue;
        int poe = restante < porEspaco ? restante : porEspaco;
        inv->espacos[i].id = id;
        inv->espacos[i].quantidade = poe;
        restante -= poe;
    }

    return qtd - restante;
}

int removerItem(Inventario *inv, int id, int qtd) {
    if (id == ITEM_NENHUM || qtd <= 0) return 0;
    if (contarItem(inv, id) < qtd) return 0;

    // Tira das ultimas pilhas primeiro, assim as primeiras ficam cheias
    int restante = qtd;
    for (int i = INVENTARIO_ESPACOS - 1; i >= 0 && restante > 0; i--) {
        if (inv->espacos[i].id != id) continue;
        int tira = restante < inv->espacos[i].quantidade
                       ? restante : inv->espacos[i].quantidade;
        inv->espacos[i].quantidade -= tira;
        restante -= tira;
        if (inv->espacos[i].quantidade == 0) inv->espacos[i].id = ITEM_NENHUM;
    }

    compactar(inv);
    return 1;
}

int listarInventario(const Inventario *inv) {
    int usados = espacosUsados(inv);

    printf("\n--- INVENTÁRIO (%d/%d espaços) ---\n", usados, INVENTARIO_ESPACOS);
    if (usados == 0) {
        printf("(vazio)\n");
        return 0;
    }

    for (int i = 0; i < INVENTARIO_ESPACOS; i++) {
        const Espaco *e = &inv->espacos[i];
        if (e->id == ITEM_NENHUM) continue;

        printf("%2d. %s", i + 1, nomeItem(e->id));
        if (itemEmpilha(e->id)) printf(" x%d", e->quantidade);
        printf(" [%s]\n", nomeTipo(tipoItem(e->id)));
    }
    return usados;
}

int validarInventario(Inventario *inv) {
    for (int i = 0; i < INVENTARIO_ESPACOS; i++) {
        const Espaco *e = &inv->espacos[i];

        if (e->id == ITEM_NENHUM) {
            if (e->quantidade != 0) return 0;
            continue;
        }
        if (!itemValido(e->id)) return 0;

        int max = itemEmpilha(e->id) ? PILHA_MAX : 1;
        if (e->quantidade < 1 || e->quantidade > max) return 0;
    }

    compactar(inv);
    return 1;
}
