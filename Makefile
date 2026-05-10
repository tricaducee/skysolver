SRCS	:= check_tab.c  check_vue.c  gen_tab.c  main.c  print_tab.c  sky_solver.c  utils.c	sky_editor.c
BIN_DIR	:= ./bin
OBJS	:= $(SRCS:%.c=$(BIN_DIR)/%.o)

FLAGS	:= -Wall -Wextra -g
CC		:= /usr/bin/gcc

TARGET	:= sky

ifeq ($(ANIMATE),1)
	FLAGS += -DANIMATE
endif

ifeq ($(OPTI),1)
	FLAGS += -O3
else
	FLAGS += -Werror
endif

all: $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(BIN_DIR) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(TARGET)

$(BIN_DIR)/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(TARGET)

re: fclean all

.PHONY: re fclean clean all