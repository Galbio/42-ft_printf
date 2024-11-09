CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS_DIR = srcs/
HEAD_DIR = includes/

SRCS = ft_printf.c \
	   writers.c

SRCS_BONUS = ft_printf_bonus.c \
			 utils_bonus.c \
			 utils2_bonus.c \
			 writers_bonus.c \
			 writers2_bonus.c \
			 flags_bonus.c

FILES = $(addprefix $(SRCS_DIR), $(SRCS))
FILES_BONUS = $(addprefix $(SRCS_DIR), $(SRCS_BONUS))

OBJS = $(FILES:.c=.o)
OBJS_BONUS = $(FILES_BONUS:.c=.o)

NAME = libftprintf.a

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rsc $(NAME) $(OBJS)

bonus : $(OBJS_BONUS)
	ar -rsc $(NAME) $(OBJS_BONUS)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@ -I $(HEAD_DIR)

clean :
	rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)
