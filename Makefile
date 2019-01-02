PROG = ft_regex.a

LIBFT = ./libft
INCLUDES = ./includes

FLAGS = -Wall -Werror -Wextra

TOOLS_FILES = ./srcs/ft_regex.c \

PROG_FILE = ./srcs/main.c

TOOLS_OBJS = $(TOOLS_FILES:.c=.o)
PROG_OBJ = $(PROG_FILE:.c=.o)

all : $(PROG)

$(PROG): $(TOOLS_OBJS)
	make -C $(LIBFT)
	ar -rcs $(PROG) $(TOOLS_OBJS)

%.o : %.c
	gcc $(FLAGS) -o $@ -c $< -I $(INCLUDES)

clean:
	make -C $(LIBFT) clean
	rm -rf $(TOOLS_OBJS)
	rm -rf $(PROG_OBJ)

fclean: clean
	make -C $(LIBFT) fclean
	rm -rf $(PROG)

re: fclean all

test: $(PROG_OBJ)
	gcc $(FLAGS) $(PROG_OBJ) $(PROG)
