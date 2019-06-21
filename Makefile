CXX         := g++
CPPFLAGS    := -g -Wall -Werror -std=c++17 -MMD -MP
IFLAGS      := -I ./src

MKDIR_P     := mkdir -p

TEST_EXEC   := data-protocol-tests
TARGET_EXEC := network-service
TEST_DIR    := tests
BUILD_DIR   := build
SRC_DIRS    := src

SRCS        := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS        := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

TEST_SRCS   := $(shell find $(tests) -name *.cpp)
TEST_OBJS   := $(TEST_SRCS:%=$(BUILD_DIR)/%.o)
TEST_DEPS   := $(OBJS:.o=.d)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@echo "[ Building $(TARGET_EXEC) ]";
	@$(CXX) $(OBJS) -o $@;

$(BUILD_DIR)/%.o: %
	@echo "[ Building $(patsubst %.cpp.o,%,$(lastword $(subst /, ,$@))) ]";
	@$(MKDIR_P) $(dir $@);
	@$(CXX) $(CPPFLAGS) $(IFLAGS) -c $< -o $@;

.PHONY: tests
tests: $(OBJS) $(TEST_OBJS)
	@$(CXX) \
	$(BUILD_DIR)/$(SRC_DIRS)/data-protocol/data-protocol.cpp.o \
	$(BUILD_DIR)/$(SRC_DIRS)/data-protocol/data-string.cpp.o \
	$(BUILD_DIR)/$(SRC_DIRS)/data-protocol/data-object.cpp.o \
	$(BUILD_DIR)/$(SRC_DIRS)/data-protocol/data-array.cpp.o \
	$(BUILD_DIR)/$(TEST_DIR)/data-protocol-tests.cpp.o \
	-o $(BUILD_DIR)/$(TEST_EXEC);

.PHONY: clean
clean:
	@echo "[ Cleaning $(BUILD_DIR) ]";
	@$(RM) -r $(BUILD_DIR);

-include $(DEPS)

