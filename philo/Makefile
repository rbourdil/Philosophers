NAME = philo

OBJS = main.o init.o start.o time.o error.o check.o string.o alone.o

HEAD = philo.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -pthread -o $(NAME)

$(OBJS):	%.o:%.c $(HEAD)
			$(CC) $(CFLAGS) -pthread -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
