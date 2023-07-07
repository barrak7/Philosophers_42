CC=cc
CFLAGS=-Wall -Wextra -Werror -pthread
#-fsanitize=thread
NAME=philo
SRC=ft_atoi.c philo_parser.c philo_utils.c philosophers.c threads_utils.c
OBJ=$(SRC:.c=.o)

.PHONEY:clean fclean re

all:$(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:clean
	rm -f $(NAME)

re:fclean all
