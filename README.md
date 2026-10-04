# RPG de Texto em C

Um jogo de RPG baseado em texto desenvolvido em C, focado em uma arquitetura modular e código limpo.

## Funcionalidades Atuais
* **Sistema de Estados:** Navegação fluida entre Menu Principal, Cidade e Exploração.
* **Sistema de Save/Load:** Persistência de dados do jogador usando arquivos binários (`.dat`).
* **Progressão:** Sistema de experiência, níveis e alocação de pontos de atributos (Força, Inteligência, Vitalidade, etc).
* **Combate:** Lógica de dano baseada na rolagem de um d20 virtual com acertos críticos e falhas.

## Como Compilar e Jogar
Recomenda-se o uso do compilador GCC. No terminal, execute:

```bash
gcc main.c cidades.c funcSistema.c jogador.c monstro.c -o jogo.exe
.\jogo.exe