# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Directories
SRC_DIR = .
BIN_DIR = ./bin
INC_DIR = .
OBJ_DIR = ./obj

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cc)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Target binaries
ENCRYPT_BIN = $(BIN_DIR)/encrypt
DECRYPT_BIN = $(BIN_DIR)/decrypt

# All target
all: $(ENCRYPT_BIN) $(DECRYPT_BIN)

# Create bin and obj directories if they don't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Encrypt binary
$(ENCRYPT_BIN): $(OBJ_DIR)/Encrypt.o $(OBJ_DIR)/BigInt.o $(OBJ_DIR)/RSA.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Decrypt binary
$(DECRYPT_BIN): $(OBJ_DIR)/Decrypt.o $(OBJ_DIR)/BigInt.o $(OBJ_DIR)/RSA.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean

