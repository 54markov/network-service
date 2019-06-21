CXX         := g++
CPPFLAGS    := -g -Wall -Werror -std=c++17 -MMD -MP
IFLAGS      := -I ./src

MKDIR_P     := mkdir -p

TARGET_EXEC := network-service
BUILD_DIR   := build
SRC_DIRS    := src

SRCS        := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS        := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@echo "[ Building $(TARGET_EXEC) ]";
	@$(CXX) $(OBJS) -o $@;

$(BUILD_DIR)/%.o: %
	@echo "[ Building $(patsubst %.cpp.o,%,$(lastword $(subst /, ,$@))) ]";
	@$(MKDIR_P) $(dir $@);
	@$(CXX) $(CPPFLAGS) $(IFLAGS) -c $< -o $@;

.PHONY: clean
clean:
	@echo "[ Cleaning $(BUILD_DIR) ]";
	@$(RM) -r $(BUILD_DIR);

-include $(DEPS)

