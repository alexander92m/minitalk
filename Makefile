NAME		=	minitalk
SERVER		=	server
CLIENT		=	client
SRC_S		=	SRC_1/server/server.c
SRC_C		=	SRC_1/client/client.c
OBJ_S		=	$(SRC_S:.c=.o)
OBJ_C		=	$(SRC_C:.c=.o)
LIBFTDIR	=	SRC_0/libft
LIBFT		=	$(LIBFTDIR)/libft.a
HEADER		=	SRC_1/minitalk.h
CFLAGS		=	-Wall -Werror -Wextra
CC			=	clang

all			:	$(NAME)

$(NAME)		:	$(SERVER) $(CLIENT) 

$(SERVER)	:	$(OBJ_S) $(LIBFT)
			$(CC) -o $@ $(OBJ_S) $(LIBFT)

$(CLIENT)	:	$(OBJ_C) $(LIBFT)
			$(CC) -o $@ $(OBJ_C) $(LIBFT)

$(LIBFT)	: Makefile
			make -C $(LIBFTDIR)

%.o			:	%.c Makefile $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean		:
			rm -f $(OBJ_S) $(OBJ_C)
			make -C $(LIBFTDIR) clean

fclean		:	clean
			rm -f $(SERVER) $(CLIENT) $(LIBFT)

re			:	fclean all

.PHONY: all libft clean fclean re