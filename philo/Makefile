NAME = philo
CC = cc
CFLAGS = -pthread -g
SRC = main.c init.c utils.c
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