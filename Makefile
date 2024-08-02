NAME = univ

SRC = src
INCLUDE = include
BUILD = build
BIN = bin
INSTALL = $(HOME)/.local
TEST := main

TARGET = $(BIN)/lib$(NAME).a
TEST_TARGET = $(BIN)/$(NAME)_test
SRCS := $(shell find $(SRC) -name '*.c' -not -name '$(TEST).c' -print)
HDRS := $(SRCS:$(SRC)/%.c=$(INCLUDE)/%.h)
OBJS := $(SRCS:$(SRC)/%.c=$(BUILD)/%.o)
TEST_OBJ = $(BUILD)/$(TEST).o

CC = clang
INCLUDE_FLAGS = -I$(INCLUDE) -include base.h
WFLAGS = -Wall -Wextra -Werror -Wno-unused-function -Wno-unused-parameter -pedantic
CFLAGS = -g -O0 -std=c89 $(WFLAGS) $(INCLUDE_FLAGS)
LDFLAGS =

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	@echo $<
	$(AR) rcs $@ $(OBJS)

$(TEST_TARGET): $(OBJS) $(TEST_OBJ)
	@mkdir -p $(dir $@)
	@echo $<
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(TEST_OBJ) -o $@

$(BUILD)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: test
test: $(TEST_TARGET)
	$(TEST_TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD)
	rm -rf $(BIN)

.PHONY: install
install: $(TARGET)
	@mkdir -p $(INSTALL)/include/$(NAME)
	@mkdir -p $(INSTALL)/lib
	cp $(INCLUDE)/base.h $(INSTALL)/include/$(NAME)
	cp $(HDRS) $(INSTALL)/include/$(NAME)
	cp $(TARGET) $(INSTALL)/lib

.PHONY: uninstall
uninstall:
	rm -f $(INSTALL)/include/$(NAME)/base.h
	rm -rf $(INSTALL)/include/$(NAME)
	rm -f $(INSTALL)/lib/lib$(NAME).a
