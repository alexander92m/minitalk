NAME = libft.a

LH = libft.h

SRC =	$(wildcard *.c)

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = clang
AR = ar
ARFLAGS = -rcs

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(ARFLAGS) $@ $?

%.o : %.c $(LH)
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
