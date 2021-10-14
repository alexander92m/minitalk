NAME			=	minitalk
SERVER			=	SRC_1/server
CLIENT			=	SRC_1/client
SERVER_B		=	SRC_1_bonus/server
CLIENT_B		=	SRC_1_bonus/client
SRC_S			=	SRC_1/server.c
SRC_C			=	SRC_1/client.c
OBJ_S			=	$(SRC_S:.c=.o)
OBJ_C			=	$(SRC_C:.c=.o)
SRC_S_B			=	SRC_1_bonus/server_bonus.c
SRC_C_B			=	SRC_1_bonus/client_bonus.c
OBJ_S_B			=	$(SRC_S_B:.c=.o)
OBJ_C_B			=	$(SRC_C_B:.c=.o)
HEADER			=	SRC_1/minitalk.h
HEADER_B		=	SRC_1_bonus/minitalk_bonus.h
LIBFTDIR		=	SRC_0/libft
LIBFT			=	$(LIBFTDIR)/libft.a

CFLAGS			=	-Wall -Werror -Wextra
CC				=	clang

all				:	$(NAME)

$(NAME)			:	$(SERVER) $(CLIENT) 

$(SERVER)		:	$(OBJ_S) $(LIBFT)
				$(CC) -o $@ $(OBJ_S) $(LIBFT)

$(CLIENT)		:	$(OBJ_C) $(LIBFT)
				$(CC) -o $@ $(OBJ_C) $(LIBFT)

%_bonus.o		:	%_bonus.c Makefile $(HEADER_B)
				$(CC) $(CFLAGS) -c $< -o $@

%.o				:	%.c Makefile $(HEADER)
				$(CC) $(CFLAGS) -c $< -o $@

bonus			:	$(SERVER_B) $(CLIENT_B) 

$(SERVER_B) 	:	$(OBJ_S_B) $(LIBFT)
				$(CC) -o $@ $(OBJ_S_B) $(LIBFT)

$(CLIENT_B)	:	$(OBJ_C_B) $(LIBFT)
				$(CC) -o $@ $(OBJ_C_B) $(LIBFT)

$(LIBFT)		: Makefile
				make -C $(LIBFTDIR)

clean			:
				rm -f $(OBJ_S) $(OBJ_C) $(OBJ_S_B) $(OBJ_C_B)
				make -C $(LIBFTDIR) clean

fclean			:	clean
				rm -f $(SERVER) $(CLIENT) $(LIBFT) $(CLIENT_B) $(SERVER_B)

re				:	fclean all

.PHONY: all libft clean fclean re bonus