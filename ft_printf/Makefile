CC				= cc

CCFLAGS 		= -Wall -Werror -Wextra

SOURCE_FILES 	= ft_printf.c print_chars.c print_numbers.c

OBJECT_FILES 	= $(SOURCE_FILES:.c=.o)

NAME = libftprintf.a

LIB = ar -rcs

RM = rm -f

all: $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(NAME): $(OBJECT_FILES)
	$(LIB) $@ $(OBJECT_FILES) 

clean:
	$(RM) $(OBJECT_FILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

