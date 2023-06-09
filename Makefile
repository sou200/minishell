NAME = minishell
CFLAGS = #-Wall -Werror -Wextra 
RM = rm -f
CC = cc

LIBFT_DIR = ./libft
SRCS = minishell.c
OBJS = $(SRCS:.c=.o)

.PHONY : all clean fclean re bonus

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBFT) -o $@ -lreadline

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean :
	$(RM) $(OBJS)
fclean : clean
	$(RM) $(NAME)
re : fclean all