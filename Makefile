# Definições de diretórios
INCLUDE_DIR = libs/SFML-2.6.1/include
INCLUDE_DIR2 = libs/Gamelib
LIB_DIR = libs/SFML-2.6.1/lib
SRC_DIR = src
BIN_DIR = bin

# Nome do executável
TARGET = $(BIN_DIR)/main

# Compilador e flags
CXX = g++
CXXFLAGS = -I$(INCLUDE_DIR) -I$(INCLUDE_DIR2) -g
LDFLAGS = -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system

# Arquivos fonte e objeto
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Regra padrão
all: $(TARGET)

# Linkagem do executável
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

# Compilação dos arquivos fonte
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	del /Q $(subst /,\,$(BIN_DIR)\*.o)
	del /Q $(subst /,\,$(TARGET).exe)
else
	rm -f $(BIN_DIR)/*.o $(TARGET)
endif
