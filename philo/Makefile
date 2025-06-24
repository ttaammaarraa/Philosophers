NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
SRC = init.c  main.c  routine.c  time.c  utils.c
OBJS = $(SRC:.c=.o)
all: $(NAME)
$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
clean:
		rm -f $(OBJS)
fclean:	clean
		rm -f $(NAME)
re:	fclean all
.PHONY:	all clean fclean re
