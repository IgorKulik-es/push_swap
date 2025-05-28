
NAME = push_swap
BNAME = checker
LIBRARY = libpush_swap.a
BLIBRARY = libpush_swap_bonus.a

SRCS = push_swap_main.c lst_basics.c parsing_checks.c basic_utils.c data_cleanup.c \
manipulations.c printer.c qsort.c small_sorts.c ft_split.c sort_three.c \
qsort_utils.c step_recorder.c

OBJS = $(SRCS:%.c=%.o)

SRCSBONUS = get_next_line_bonus.c get_next_line_utils_bonus.c checker_bonus.c\
parsing_checks.c basic_utils.c manipulations.c lst_basics.c step_recorder.c data_cleanup.c\
ft_split.c

OBJBONUS = $(SRCSBONUS:%.c=%.o)

HEADER = push_swap.h
BHEADER = get_next_line_bonus.h



CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME)

$(NAME): $(LIBRARY)
	cc -o $(NAME) $(LIBRARY) -g

$(LIBRARY): $(OBJS)
	ar -rcs -o $(LIBRARY) $(OBJS) $(HEADER)

bonus: $(BNAME)

$(BNAME): $(BLIBRARY)
	cc -o $(BNAME) $(BLIBRARY) -g

$(BLIBRARY): $(OBJBONUS)
	ar -rcs -o $(BLIBRARY) $(OBJBONUS) $(HEADER) $(BHEADER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -g

clean:
	$(RM) $(OBJS) $(OBJBONUS)

fclean: clean
	$(RM) $(NAME) $(BNAME) $(LIBRARY) $(BLIBRARY)

re: fclean all
