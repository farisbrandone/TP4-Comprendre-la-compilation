# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra -fPIC
LDFLAGS = -shared
LIBS = -lm

# Directories
SRC_DIR = src
LIB_DIR = $(SRC_DIR)/lib/calstatlib
BUILD_DIR = $(SRC_DIR)/buildForDynamiqueLib
BIN_DIR = $(SRC_DIR)/bin

# Include paths for libraries
LIB_INCLUDES = -I $(LIB_DIR)/tokenType

# Include paths for main application
MAIN_INCLUDES = -I $(LIB_DIR)/tokenize \
                -I $(LIB_DIR)/shuntingYard \
                -I $(LIB_DIR)/fixUnaryMinus \
                -I $(LIB_DIR)/evalRpn \
                -I $(LIB_DIR)/tokenType

# Library targets
LIBRARIES = evalRpn fixUnaryMinus shuntingYard tokenize
LIB_OBJECTS = $(addprefix $(BUILD_DIR)/, $(addsuffix /$(addsuffix .o, $(LIBRARIES)))
LIB_SO_FILES = $(addprefix $(BUILD_DIR)/, $(addsuffix /$(addsuffix .so, $(LIBRARIES)))

# Main application
MAIN_OBJ = $(BUILD_DIR)/app/main.o
EXECUTABLE = $(BIN_DIR)/exeWithDynLib

# Default target
all: $(EXECUTABLE)

# Create executable
$(EXECUTABLE): $(MAIN_OBJ) $(LIB_SO_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) -g -o $@ $(MAIN_OBJ) \
	    -I $(BUILD_DIR)/evalRpn \
	    -I $(BUILD_DIR)/fixUnaryMinus \
	    -I $(BUILD_DIR)/shuntingYard \
	    -I $(BUILD_DIR)/tokenize \
	    $(BUILD_DIR)/evalRpn/evalRpn.so \
	    $(BUILD_DIR)/fixUnaryMinus/fixUnaryMinus.so \
	    $(BUILD_DIR)/shuntingYard/shuntingYard.so \
	    $(BUILD_DIR)/tokenize/tokenize.so \
	    $(LIBS)

# Main object file
$(BUILD_DIR)/app/main.o: $(SRC_DIR)/app/main.c
	@mkdir -p $(BUILD_DIR)/app
	$(CC) $(CFLAGS) $(MAIN_INCLUDES) -c $< -o $@

# evalRpn shared library
$(BUILD_DIR)/evalRpn/evalRpn.so: $(BUILD_DIR)/evalRpn/evalRpn.o
	@mkdir -p $(BUILD_DIR)/evalRpn
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

$(BUILD_DIR)/evalRpn/evalRpn.o: $(LIB_DIR)/evalRpn/evalRpn.c
	@mkdir -p $(BUILD_DIR)/evalRpn
	$(CC) $(CFLAGS) $(LIB_INCLUDES) -c $< -o $@

# fixUnaryMinus shared library
$(BUILD_DIR)/fixUnaryMinus/fixUnaryMinus.so: $(BUILD_DIR)/fixUnaryMinus/fixUnaryMinus.o
	@mkdir -p $(BUILD_DIR)/fixUnaryMinus
	$(CC) $(LDFLAGS) -o $@ $<

$(BUILD_DIR)/fixUnaryMinus/fixUnaryMinus.o: $(LIB_DIR)/fixUnaryMinus/fixUnaryMinus.c
	@mkdir -p $(BUILD_DIR)/fixUnaryMinus
	$(CC) $(CFLAGS) $(LIB_INCLUDES) -c $< -o $@

# shuntingYard shared library
$(BUILD_DIR)/shuntingYard/shuntingYard.so: $(BUILD_DIR)/shuntingYard/shuntingYard.o
	@mkdir -p $(BUILD_DIR)/shuntingYard
	$(CC) $(LDFLAGS) -o $@ $<

$(BUILD_DIR)/shuntingYard/shuntingYard.o: $(LIB_DIR)/shuntingYard/shuntingYard.c
	@mkdir -p $(BUILD_DIR)/shuntingYard
	$(CC) $(CFLAGS) $(LIB_INCLUDES) -c $< -o $@

# tokenize shared library
$(BUILD_DIR)/tokenize/tokenize.so: $(BUILD_DIR)/tokenize/tokenize.o
	@mkdir -p $(BUILD_DIR)/tokenize
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

$(BUILD_DIR)/tokenize/tokenize.o: $(LIB_DIR)/tokenize/tokenize.c
	@mkdir -p $(BUILD_DIR)/tokenize
	$(CC) $(CFLAGS) $(LIB_INCLUDES) -c $< -o $@

# Run the program
run: $(EXECUTABLE)
	LD_LIBRARY_PATH=$(BUILD_DIR)/evalRpn:$(BUILD_DIR)/fixUnaryMinus:$(BUILD_DIR)/shuntingYard:$(BUILD_DIR)/tokenize ./$(EXECUTABLE)

# Install libraries to system path (optional)
install: $(LIB_SO_FILES)
	@echo "Installing shared libraries to /usr/local/lib/"
	sudo cp $(BUILD_DIR)/evalRpn/evalRpn.so /usr/local/lib/
	sudo cp $(BUILD_DIR)/fixUnaryMinus/fixUnaryMinus.so /usr/local/lib/
	sudo cp $(BUILD_DIR)/shuntingYard/shuntingYard.so /usr/local/lib/
	sudo cp $(BUILD_DIR)/tokenize/tokenize.so /usr/local/lib/
	sudo ldconfig

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Show file structure
tree:
	@echo "Project structure:"
	@tree $(SRC_DIR) -I '*.so|*.o' || echo "Install 'tree' command for better visualization"

# Debug info
debug:
	@echo "Library objects: $(LIB_OBJECTS)"
	@echo "Shared libraries: $(LIB_SO_FILES)"
	@echo "Main object: $(MAIN_OBJ)"
	@echo "Executable: $(EXECUTABLE)"

.PHONY: all run install clean tree debug
