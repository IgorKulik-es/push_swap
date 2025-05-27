NAME = push_swap
LIBRARY = libpush_swap.a

SRCS = push_swap_main.c lst_basics.c parsing_checks.c basic_utils.c data_cleanup.c manipulations.c \
printer.c qsort.c small_sorts.c ft_split.c sort_three.c qsort_utils.c step_recorder.c

HEADER = push_swap.h

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME)

$(NAME): $(LIBRARY)
	cc -o $(NAME) $(LIBRARY) -g

$(LIBRARY): $(OBJS)
	ar -rcs -o $(LIBRARY) $(OBJS) $(HEADER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -g

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(LIBRARY)

re: fclean all
