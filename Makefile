CC      = gcc
CFLAGS  = -Wall -Wextra
SRC     = main.c cidades.c funcSistema.c jogador.c monstro.c entrada.c

jogo: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o jogo

run:	jogo
	./jogo

clean:
	rm -f jogo jogo.exe