CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS_DIR = srcs/
HEAD_DIR = includes/

SRCS = ft_printf.c \
			 utils.c \
			 utils2.c \
			 writers.c \
			 writers2.c \
			 flags.c

FILES = $(addprefix $(SRCS_DIR), $(SRCS))

OBJS = $(FILES:.c=.o)

NAME = libftprintf.a

all : $(NAME)

bonus : $(NAME)

$(NAME) : $(OBJS)
	ar -rsc $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@ -I $(HEAD_DIR)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)
