# RPG de Texto em C

Um jogo de RPG baseado em texto desenvolvido em C, focado em uma arquitetura modular.

## Funcionalidades Atuais
* **Sistema de Estados:** Navegação fluida entre Menu Principal, Cidade e Exploração.
* **Sistema de Save/Load:** Persistência de dados do jogador usando arquivos binários
* **Progressão:** Sistema de experiência, níveis e alocação de pontos de atributos (Força, Inteligência, Vitalidade, etc).
* **Equipamentos:** Slots de arma, armadura e acessórios com bônus de ataque/defesa, peso, valor e status mínimos para equipar (tabela de itens em `equipamentos.c`).
* **Combate:** Lógica de dano baseada na rolagem de um d20 virtual com acertos com falha, criticos, dano reduzido e dano padrão.

## Como Compilar e Jogar
Requer o GCC.

```
make
```

Ou, sem o Make:

```
gcc -Wall -Wextra main.c cidades.c funcSistema.c jogador.c monstro.c entrada.c equipamentos.c -o jogo
```

Para executar:

- **Linux / macOS:** `./jogo`
- **Windows:** `.\jogo.exe`