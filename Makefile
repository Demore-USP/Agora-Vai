# Variáveis
CC = gcc # Compilador
CFLAGS = -O3 -Wall -g # Opções de compilação: otimização O3, avisos e depuração
EXEC = programa # Nome do executável
OBJ = app.o ListaProduto.o ListaUsuario.o PilhaLances.o Fila.o Lista.o # Arquivos objeto

# Regra padrão
all: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Regras para compilar os arquivos objeto
app.o: app.c ListaProduto.h ListaUsuario.h PilhaLances.h Fila.h Lista.h
	$(CC) $(CFLAGS) -c app.c

ListaProduto.o: ListaProduto.c ListaProduto.h
	$(CC) $(CFLAGS) -c ListaProduto.c

ListaUsuario.o: ListaUsuario.c ListaUsuario.h
	$(CC) $(CFLAGS) -c ListaUsuario.c

PilhaLances.o: PilhaLances.c PilhaLances.h
	$(CC) $(CFLAGS) -c PilhaLances.c

Fila.o: Fila.c Fila.h
	$(CC) $(CFLAGS) -c Fila.c

Lista.o: Lista.c Lista.h
	$(CC) $(CFLAGS) -c Lista.c

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)