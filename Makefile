
TAB_SIZE = 4
UNAME_S := $(shell uname -s)
NAME = minivim
#NAME = mvm
BIN_DIR ?= /usr/local/bin
CC = gcc
# flags
CFLAGS += -D TAB_SIZE=$(TAB_SIZE)
CURSOR_HL ?= 1
CFLAGS += -D CURSOR_HL=$(CURSOR_HL)
CFLAGS += -I ./inc
#LDFLAGS = -L ./inc
RM = rm
RMFLAGS = -rf
SRC_PATH = src
OBJ_PATH = obj
SRC_FILES =		main.c			init.c			input.c			\
				output.c		append_buff.c	find.c			\
				file_io.c		editor_ops.c	row_ops.c		\
				syntax_hl.c		terminal.c

OBJ_FILES = $(SRC_FILES:%.c=%.o)
SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_FILES))
.PHONY: all dev clean fclean re

all: $(NAME)

install: $(NAME)
	install $(NAME) $(BIN_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	make -f inc/makefile

ifeq ($(UNAME_S),Linux)
sanitize: CFLAGS += -pedantic -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -g3
endif
ifeq ($(UNAME_S),Darwin)
sanitize: CFLAGS += -pedantic -fsanitize=address -g3
endif
sanitize: $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH) 2> /dev/null

clean:
	$(RM) $(RMFLAGS) $(OBJ_PATH)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all




