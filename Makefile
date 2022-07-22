#------------------------------------------------------------------------------
# EZClientCpp - Exemplo de acesso a EZCLient.dll(.so)
#
#   Empresa: EZTech Tecnologia
#			 http://www.eztech.ind.br/
#
#   Data   : 22/07/2022 
#
# Observacoes: 
#
#
#		*. para compilar com GCC para Windows ou Linux utilize o script Makefile
#		   utilize os seguintes comandos:
#
#				> make clean   (limpa objetos antigos)
#				> make linux   (plataforma LINUX 32bits)
#				> make windows (plataforma WIN32)
#
#------------------------------------------------------------------------------
PRJ	= EZClientCpp
BIN	= bin

DEPS= -lpthread -ldl

OUT = $(BIN)/$(PRJ)

RES	= windres -v -I../ -i

# 32 bit 
# GCC	= g++ -m32 -Os -Wall -Wno-deprecated -c -Wno-write-strings -Wno-format -Wno-unused-result
# LNK	= g++ -m32 -static-libgcc -static-libstdc++

# 64 bit 
GCC	= g++ -Os -Wall -Wno-deprecated -c -Wno-write-strings -Wno-format -Wno-unused-result
LNK	= g++ -static-libgcc -static-libstdc++

OBJ = $(BIN)/ClientMain.o	$(BIN)/EZClient.o
WRC = $(BIN)/EZClientCpp.o

#------------------------------------------------------------------------------
linux:	$(OUT)
	@echo -e "\n\n--- Versao Linux finalizada: $<"

#------------------------------------------------------------------------------
windows:	$(OUT).exe
	@echo -e "\n\n--- Versao Windows finalizada: $<"

#------------------------------------------------------------------------------
# Linkagem para versao Linux
$(OUT):	$(BIN)	$(OBJ)
	@echo -e "\n\n--- Gerando $@"
	$(LNK) $(LIB) $(OBJ) -o $@ $(DEPS)
	rm -fv $(BIN)/*.o

#------------------------------------------------------------------------------
# Linkagem para versao Windows
$(OUT).exe:	$(BIN)	$(OBJ)	$(WRC)
	@echo -e "\n\n--- Gerando $@"
	$(LNK) $(LIB) $(OBJ) $(WRC) -o $@
	@rm -fv $(BIN)/*.o

#------------------------------------------------------------------------------
# Compila arquivo de recursos (somente para Windowa)
$(WRC):	EZClientCpp.rc
	@echo -e "\n\n--- Compilando $<"
	$(RES) $< -o $@ 

#------------------------------------------------------------------------------
# Compila arquivos fonte
$(BIN)/%.o:	%.cpp
	@echo -e "\n\n-- Compilando $<"
	$(GCC) $(INC) -o $@ $< 

#------------------------------------------------------------------------------
installlib: EZLib/libezclient.so.1.0
	@echo -e "\n\n--- Instalando biblioteca para plataforma Linux..."
	@echo -e "\n\n    (esta operacao deve ser executada pelo usuario root)"	
	@cp -fv  EZLib/libezclient.so.1.0 /usr/lib
	@ln -fsv /usr/lib/libezclient.so.1.0 /usr/lib/libezclient.so.1
	@ln -fsv /usr/lib/libezclient.so.1.0 /usr/lib/libezclient.so

#------------------------------------------------------------------------------
# Cria Subdiretorio de binarios
$(BIN):
	@echo -e "\n\n--- Criando diretorio de binarios: $<"
	@mkdir -p $@
	
#------------------------------------------------------------------------------
# Limpa arquivos de compilacao
clean:
	@rm -fv $(BIN)/*
	
#------------------------------------------------------------------------------
