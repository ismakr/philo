C_FILES = parse.c parse_utils.c threads_logic.c threads_logic_utils.c threads_create.c main.c
O_FILES = $(C_FILES:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g
NAME = philo

all: $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(O_FILES)
	$(CC) $(O_FILES) -o $(NAME)

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
