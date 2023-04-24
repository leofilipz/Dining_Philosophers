CC = cc -g
CFLAGS = -Wall -Werror -Wextra -pthread -fsanitize=thread
NAME = philo

SRCS = utils.c philo.c confirm.c create.c threads.c actions.c printings.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

${NAME}: ${OBJS}	
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS) objs
	
fclean: clean
	rm -f $(NAME)

re: fclean all