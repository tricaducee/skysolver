SRCS	:= check_tab.c  check_vue.c  gen_tab.c  main.c  print_tab.c  sky_solver.c  utils.c
OBJS	:= $(SRCS:%.c=%.o)

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

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(TARGET)

re: fclean all

.PHONY: re fclean clean all