SRC = ft_isalpha ft_isdigit ft_isalnum ft_isascii \
		ft_isprint ft_toupper ft_tolower ft_atoi \
		ft_strlen ft_strlcpy ft_strlcat ft_strncmp ft_strrchr \
		ft_strchr ft_strnstr ft_strdup ft_memset \
		ft_memcpy ft_memmove ft_memchr ft_memcmp \
		ft_calloc ft_bzero ft_substr ft_strjoin \
		ft_strtrim ft_split ft_itoa ft_putchar_fd \
		ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_itoa \
		ft_strmapi ft_striteri ft_lstnew_bonus ft_lstadd_front_bonus \
		ft_lstsize_bonus ft_lstlast_bonus \
		ft_lstadd_back_bonus ft_lstdelone_bonus ft_lstclear_bonus \
		ft_lstiter_bonus ft_lstmap_bonus

SRCS = $(addsuffix .c, $(SRC))

CC = cc
NAME = libft.a
CFLAGS = -Wextra -Wall -Werror
RM = rm -rf

OBJS = $(SRCS:.c=.o)

all : $(NAME) 

$(NAME) : $(OBJS) libft.h
	ar rcs $@ $?

clean :
	$(RM) $(OBJS)
fclean : clean
	$(RM) $(NAME)
re : fclean all

.PHONY: all bonus clean fclean re
