#Compilador
COMPILADOR = g++

#Nome do seu executavel
NOME_EXECUTAVEL = Forca

#Diretorio dos arquivos binarios
BIN = ./bin

#Diretorio dos arquivos .h e .hpp
INCLUDE = ./include

#Diretorio dos arquivos .c e .cpp
SRC = ./src

#Para otimizar e mostrar mais avisos
FLAGS = -g -Wall -ansi -pedantic -O0

#Fontes .cpp
FONTES = $(wildcard $(SRC)/*.cpp)

#Retirar prefixo e sufixo
OBJLIMPAR = $(notdir $(basename $(FONTES)))

#Adicionar novo prefixo e sufixo
OBJETOS = $(addprefix $(BIN)/, $(addsuffix .o, $(OBJLIMPAR)))

.PHONY: all cleanObjetos clean tar

all: $(NOME_EXECUTAVEL)

#Compilar e criar os arquivos-objetos
$(BIN)/%.o: $(SRC)/%.cpp
	$(COMPILADOR) $(FLAGS) -c "$<" -o "$@"

#Linkar e criar o executavel
$(NOME_EXECUTAVEL): $(OBJETOS)
	$(COMPILADOR) $(FLAGS) $(OBJETOS) -o $(BIN)/$@

#Executar programa
run:
	$(BIN)/$(NOME_EXECUTAVEL)

#Limpar arquivos .o
cleanObjetos:
	rm -f $(BIN)/*.o

#Limpar executavel
clean:
	rm -f $(BIN)/$(NOME_EXECUTAVEL)