NAME = minishell
# CFLAGS = -fsanitize=address -g3
RM = rm -f
CC = cc

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS = minishell.c lexer/lexer.c lexer/tokenization.c parser/quotes_handler.c \
	parser/syntax_error_handler.c expander/expander.c tools/leaks.c \
	tools/recyclable.c  lexer/ft_free_token.c lexer/token_utils.c parser/quotes_handler.c parser/syntax_error_handler.c parser/cmnd_builder.c \
	parser/parser.c expander/expand_utils.c expander/expander.c tools/ft_strjoin_free.c builtins/env.c \
	builtins/cmds.c builtins/get_next_line_bonus.c builtins/get_next_line_utils_bonus.c builtins/echo.c \
	builtins/sorted_lst.c builtins/cd.c builtins/pwd.c builtins/heredoc.c builtins/redirections.c \
	builtins/cmds2.c

OBJS = $(SRCS:.c=.o)


all : $(NAME)

HOME :
	@echo \#/Users/`whoami` >> Makefile
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

.PHONY : all clean fclean re bonus
#/Users/fel-hazz
#/Users/fel-hazz
