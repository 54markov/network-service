SRC_DIR     := src
BUILD_DIR   := build
INCLUDE_DIR := include
TARGET      := network-service
OBJ         := socket tcp udp data-protocol exception client server

CC          := g++
CFLAGS      := -g -Wall -Werror -std=c++17
IFLAGS      := -I ./include

all: socket tcp udp data-protocol exception client server $(TARGET)

$(TARGET):
	@echo "Building $@ ...";
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -o $(BUILD_DIR)/$(TARGET) \
	$(BUILD_DIR)/client.o \
	$(BUILD_DIR)/server.o \
	$(BUILD_DIR)/data-protocol.o \
	$(BUILD_DIR)/exception.o \
	$(BUILD_DIR)/socket.o \
	$(BUILD_DIR)/tcp.o \
	$(BUILD_DIR)/udp.o \
	$(SRC_DIR)/main.cpp

client:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/service/$@.cpp

server:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/service/$@.cpp

exception:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/$@/$@.cpp

data-protocol:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/$@/$@.cpp

tcp:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/socket/$@.cpp

udp:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/socket/$@.cpp

socket:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/$@/$@.cpp

clean:
	@echo "[ Cleaning $(BUILD_DIR) ]";
	@rm -Rf $(BUILD_DIR);
