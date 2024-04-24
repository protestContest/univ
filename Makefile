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
CFLAGS = -g -std=c89 $(WFLAGS) $(INCLUDE_FLAGS)
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
	rm -rf $(TARGET)

.PHONY: install
install: $(TARGET)
	@mkdir -p $(INSTALL)/include
	@mkdir -p $(INSTALL)/lib
	@rm -f $(INSTALL)/include/$(NAME).h
	cp $(INCLUDE)/base.h $(INSTALL)/include/base.h
	cat $(HDRS) > $(INSTALL)/include/$(NAME).h
	cp $(TARGET) $(INSTALL)/lib

.PHONY: uninstall
uninstall:
	rm -f $(INSTALL)/include/base.h
	rm -f $(INSTALL)/include/$(NAME).h
	rm -f $(INSTALL)/lib/lib$(NAME).a
