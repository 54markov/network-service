SRC_DIR     := src
BUILD_DIR   := build
TARGET      := network-service
OBJ         := socket tcp udp data-protocol exception client server

CC          := g++
CFLAGS      := -g -Wall -Werror -std=c++17
IFLAGS      := -I ./src

all: socket tcp udp data-protocol exception client server signal $(TARGET)

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
	$(BUILD_DIR)/signal.o \
	$(SRC_DIR)/main.cpp

signal:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/service/$@.cpp

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
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/network/$@.cpp

udp:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/network/$@.cpp

socket:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/network/$@.cpp

clean:
	@echo "[ Cleaning $(BUILD_DIR) ]";
	@rm -Rf $(BUILD_DIR);
