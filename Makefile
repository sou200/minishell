NAME = minishell
CFLAGS = #-Wall -Werror -Wextra 
RM = rm -f
CC = cc

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS = minishell.c lexer/lexer.c lexer/tokenization.c parser/quotes_handler.c
OBJS = $(SRCS:.c=.o)

.PHONY : all clean fclean re bonus

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -lreadline -L$(shell brew --prefix readline)/lib $(LIBFT) $^ -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@
clean :
	make -C $(LIBFT_DIR) $@
	$(RM) $(OBJS)
fclean : clean
	make -C $(LIBFT_DIR) $@
	$(RM) $(NAME)
re : fclean all