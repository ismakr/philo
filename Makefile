C_FILES = ft_strjoin.c parse_utils.c args.c main.c ft_split.c
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
