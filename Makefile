PROG = libregex.a

LIBFT = ./libft
INCLUDES = ./includes

FLAGS = -Wall -Werror -Wextra

TOOLS_FILES = 	./srcs/ft_regex.c \
		./srcs/pattern_parser.c \
		./srcs/mem_fct.c \
		./srcs/expr_fct.c

PROG_FILE = ./srcs/main.c

TOOLS_OBJS = $(TOOLS_FILES:.c=.o)
PROG_OBJ = $(PROG_FILE:.c=.o)

all : $(PROG)

$(PROG): lib $(TOOLS_OBJS)
	ar -rcs $(PROG) $(TOOLS_OBJS)

lib:
	cd $(LIBFT) && make

%.o : %.c
	gcc $(FLAGS) -o $@ -c $< -I $(INCLUDES) -I $(LIBFT)

clean:
	make -C $(LIBFT) clean
	rm -rf $(TOOLS_OBJS)
	rm -rf $(PROG_OBJ)

fclean: clean
	make -C $(LIBFT) fclean
	rm -rf $(PROG)
	rm -rf regex

re: fclean all

test: all $(PROG_OBJ)
	gcc $(FLAGS) -o regex $(PROG_OBJ) -L $(LIBFT) -lft -L . -lregex
