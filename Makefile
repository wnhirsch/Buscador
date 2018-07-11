### Makefile ###

# Name of the Project
PROJ_NAME=buscador

#Macros
# .c files
C_SOURCE=$(wildcard sources/*.c)
	# sources/abp.c sources/main.c

# .h files
H_SOURCE=$(wildcard headers/*.h)
	# headers/abp.h

# Object files
#OBJ=$(C_SOURCE:.c=.o)
	# sources/abp.o sources/main.o
OBJ=$(subst .c,.o,$(subst sources,objects,$(C_SOURCE)))

# compiler
CC=gcc

#Flags for compiler
# modo com mais warnings:
#CFLAGS=-c -W -Wall -ansi -pedantic
# modo mais direto:
CFLAGS=-c -W -Wall -pedantic

# Compilation and linking

all: $(PROJ_NAME)
	@ echo ''
	@ echo 'Testando codigo'
	@ ./buscador	minor_entrada.txt	minor_op.txt	minor_saida.txt

$(PROJ_NAME): $(OBJ)
	@ echo ''
	@ echo '    Building binary using GCC linker: $@'
	$(CC) -o $@ $^ -lm
	@ echo '    Finished Building binary: $@'

./objects/%.o: ./sources/%.c ./headers/%.h
	@ echo '    compiling: $(subst objects/,,$@)'
	$(CC) $(CFLAGS) $< -o $@

./objects/main.o: ./sources/main.c $(H_SOURCE)
	@ echo ''
	@ echo '    compiling main.o'
	$(CC) $(CFLAGS) $< -o $@

./objects/teste.o: ./sources/teste.c
	@ echo 'compilando $@'
	$(CC) $(CFLAGS) -o ./objects/teste.o $^

teste: ./objects/lde.o ./objects/abp.o ./objects/lde_circular.o ./objects/teste.o
	$(CC) -o teste $^
	@ echo 'Testando:'
	@ ./teste	minor_entrada.txt	minor_op.txt	minor_saida.txt

clean:
	@ echo '    removing old archives'
	rm -rf ./objects/*.o ./sources/*.o $(PROJ_NAME)
	@ echo ''

debug:
	@ echo 'C_SOURCE $(C_SOURCE)'
	@ echo 'H_SOURCE $(H_SOURCE)'
	@ echo 'OBJ $(OBJ)'


# Macros - significados:
# <wildcard> pega todos os nomes de arquivos que seguem aquela regra
# separa os nomes dos arquivos por espaços

# % - pega o stem (tronco) do nome. que é utilizado de referência no pré-requisito

# variáveis automáticas:
# $@ pega o nome do target
# $< pega o primeiro pré-requisito
