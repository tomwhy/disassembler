CC=gcc
CFLAGS=-Wall -Werror
LDFLAGS=
MAKEFLAGS+=--silent

ifdef SPARSE
	CC:=cgcc
	CFLAGS+=-Wsparse-all -Wno-unknown-attribute -Wsparse-error
endif

OUT=output
BIN=dis

SRC_DIR=src
SRCS=$(SRC_DIR)/main.c \
     $(SRC_DIR)/opcode.c

BIN_DIR=$(OUT)/bin
OBJS_DIR=$(OUT)/obj
DEPS_DIR=$(OUT)/deps

BIN_PATH=$(BIN_DIR)/$(BIN)

OBJS=$(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))
DEPS=$(patsubst $(SRC_DIR)/%.c, $(DEPS_DIR)/%.d, $(SRCS))

all: $(BIN_PATH)

clean:
	-@rm -r $(OUT) $(SRC_DIR)/gen 2>/dev/null

-include $(DEPS)

$(BIN_PATH): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "[LD]  $(notdir $(BIN_PATH))"
	@$(CC) $(LDFLAGS) $^ -o $@


$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "[CC]  $(notdir $<)"
	@$(CC) $(CFLAGS) -c $< -o $@

	@mkdir -p $(dir $(patsubst $(SRC_DIR)/%.c, $(DEPS_DIR)/%.d, $<))
	@echo "[DEP] $(notdir $<)"
	@$(CC) $(CFLAGS) -MM -MT $@ $< > $(patsubst $(SRC_DIR)/%.c, $(DEPS_DIR)/%.d, $<)

.PHONY: all clean
