SRC_DIR     := src
BUILD_DIR   := build
TARGET      := network-service
TEST        := data-protocol-tests
NETWORK     := socket tcp udp
SERVICE     := client server
DATA        := data-protocol data-object data-array data-string
UTIL        := signal exception cpu-monitor

CC          := g++
CFLAGS      := -g -Wall -Werror -std=c++17
IFLAGS      := -I ./src

all: $(NETWORK) $(SERVICE) $(DATA) $(UTIL) $(TARGET) $(TEST)

$(TARGET):
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -o $(BUILD_DIR)/$(TARGET) \
	$(BUILD_DIR)/client.o \
	$(BUILD_DIR)/server.o \
	$(BUILD_DIR)/data-protocol.o \
	$(BUILD_DIR)/data-string.o \
	$(BUILD_DIR)/data-object.o \
	$(BUILD_DIR)/data-array.o \
	$(BUILD_DIR)/exception.o \
	$(BUILD_DIR)/socket.o \
	$(BUILD_DIR)/tcp.o \
	$(BUILD_DIR)/udp.o \
	$(BUILD_DIR)/signal.o \
	$(BUILD_DIR)/cpu-monitor.o \
	$(SRC_DIR)/main.cpp

$(TEST):
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -o $(BUILD_DIR)/data-protocol-tests \
	./tests/data-protocol-tests.cpp \
	$(BUILD_DIR)/data-protocol.o \
	$(BUILD_DIR)/data-string.o \
	$(BUILD_DIR)/data-object.o \
	$(BUILD_DIR)/data-array.o

cpu-monitor:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/$@/$@.cpp

signal:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/service/$@.cpp

exception:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/$@/$@.cpp

socket:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/network/$@.cpp
tcp:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/network/$@.cpp

udp:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/network/$@.cpp

client:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/service/$@.cpp

server:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/service/$@.cpp

data-protocol:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/$@/$@.cpp

data-object:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/data-protocol/$@.cpp

data-array:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/data-protocol/$@.cpp

data-string:
	@echo "[ Building $@ ]";
	@mkdir -p $(BUILD_DIR);
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $(BUILD_DIR)/$@.o $(SRC_DIR)/data-protocol/$@.cpp

clean:
	@echo "[ Cleaning $(BUILD_DIR) ]";
	@rm -Rf $(BUILD_DIR);
