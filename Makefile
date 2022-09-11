NAME = philo

OBJS = main.o init.o start.o eat_sleep_think.o check_death.o free.o utils.o error.o

HEADS = philo.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) -pthread $(OBJS) -o $(NAME)

$(OBJS):	%.o:%.c $(HEADS)
			$(CC) $(CFLAGS) -pthread -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
