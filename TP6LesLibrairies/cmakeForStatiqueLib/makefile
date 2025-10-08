# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra
AR = ar
ARFLAGS = rcs

# Directories
SRC_DIR = src
LIB_DIR = $(SRC_DIR)/lib/calstatlib
BUILD_DIR = $(SRC_DIR)/build
BIN_DIR = $(SRC_DIR)/bin

# Include paths
INCLUDES = -I $(LIB_DIR)/tokenType \
           -I $(LIB_DIR)/tokenize \
           -I $(LIB_DIR)/shuntingYard \
           -I $(LIB_DIR)/fixUnaryMinus \
           -I $(LIB_DIR)/evalRpn

# Library targets
LIBS = evalRpn fixUnaryMinus shuntingYard tokenize
LIB_OBJS = $(addprefix $(BUILD_DIR)/, $(addsuffix /%.o, $(LIBS)))
LIB_ARCHIVES = $(addprefix $(BUILD_DIR)/, $(addsuffix /%.a, $(LIBS)))

# Main application
MAIN_OBJ = $(BUILD_DIR)/app/main.o
CALCULATRICE_OBJ = $(BUILD_DIR)/app/calculatrice.o
EXECUTABLE = $(BIN_DIR)/exeWithLib

# Default target
all: $(EXECUTABLE)

# Create executable
$(EXECUTABLE): $(MAIN_OBJ) $(CALCULATRICE_OBJ) $(addprefix $(BUILD_DIR)/, $(addsuffix /$(addsuffix .a, $(LIBS)))
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJ) $(CALCULATRICE_OBJ) \
		-L$(BUILD_DIR)/evalRpn -l:evalRpn.a \
		-L$(BUILD_DIR)/fixUnaryMinus -l:fixUnaryMinus.a \
		-L$(BUILD_DIR)/shuntingYard -l:shuntingYard.a \
		-L$(BUILD_DIR)/tokenize -l:tokenize.a \
		-lm

# Main object
$(BUILD_DIR)/app/main.o: $(SRC_DIR)/app/main.c
	@mkdir -p $(BUILD_DIR)/app
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Calculatrice object
$(BUILD_DIR)/app/calculatrice.o: $(SRC_DIR)/app/calculatrice.c
	@mkdir -p $(BUILD_DIR)/app
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# evalRpn library
$(BUILD_DIR)/evalRpn/evalRpn.a: $(BUILD_DIR)/evalRpn/evalRpn.o
	@mkdir -p $(BUILD_DIR)/evalRpn
	$(AR) $(ARFLAGS) $@ $<

$(BUILD_DIR)/evalRpn/evalRpn.o: $(LIB_DIR)/evalRpn/evalRpn.c
	@mkdir -p $(BUILD_DIR)/evalRpn
	$(CC) $(CFLAGS) -I $(LIB_DIR)/tokenType -c $< -o $@

# fixUnaryMinus library
$(BUILD_DIR)/fixUnaryMinus/fixUnaryMinus.a: $(BUILD_DIR)/fixUnaryMinus/fixUnaryMinus.o
	@mkdir -p $(BUILD_DIR)/fixUnaryMinus
	$(AR) $(ARFLAGS) $@ $<

$(BUILD_DIR)/fixUnaryMinus/fixUnaryMinus.o: $(LIB_DIR)/fixUnaryMinus/fixUnaryMinus.c
	@mkdir -p $(BUILD_DIR)/fixUnaryMinus
	$(CC) $(CFLAGS) -I $(LIB_DIR)/tokenType -c $< -o $@

# shuntingYard library
$(BUILD_DIR)/shuntingYard/shuntingYard.a: $(BUILD_DIR)/shuntingYard/shuntingYard.o
	@mkdir -p $(BUILD_DIR)/shuntingYard
	$(AR) $(ARFLAGS) $@ $<

$(BUILD_DIR)/shuntingYard/shuntingYard.o: $(LIB_DIR)/shuntingYard/shuntingYard.c
	@mkdir -p $(BUILD_DIR)/shuntingYard
	$(CC) $(CFLAGS) -I $(LIB_DIR)/tokenType -c $< -o $@

# tokenize library
$(BUILD_DIR)/tokenize/tokenize.a: $(BUILD_DIR)/tokenize/tokenize.o
	@mkdir -p $(BUILD_DIR)/tokenize
	$(AR) $(ARFLAGS) $@ $<

$(BUILD_DIR)/tokenize/tokenize.o: $(LIB_DIR)/tokenize/tokenize.c
	@mkdir -p $(BUILD_DIR)/tokenize
	$(CC) $(CFLAGS) -I $(LIB_DIR)/tokenType -c $< -o $@

# Run the program
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Show help
help:
	@echo "Available targets:"
	@echo "  all     - Build everything (default)"
	@echo "  run     - Build and run the program"
	@echo "  clean   - Remove all build artifacts"
	@echo "  help    - Show this help message"

.PHONY: all run clean help
