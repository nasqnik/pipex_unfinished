CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RM 			= rm -rf

NAME 		= pipex
HEADER 		= pipex.h

SRC			= pipex.c	pipex_utils.c	pipex_errors.c
OBJ			= $(SRC:%.c=%.o)

# BONUS =
# BONUS_SRC =
# BONUS_OBJ = $(BONUS_SRC:.c=.o)

LIBFT		=	libft/libft.a
FT_PRINTF	=	ft_printf/libftprintf.a

all:		libft ft_printf $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) -o $(NAME)

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS)  -c $< -o $@

libft:
			@$(MAKE) -C libft/

ft_printf:
			@$(MAKE) -C ft_printf/

clean:
			@$(RM) $(OBJ)
			@$(MAKE) -C libft/ clean
			@$(MAKE) -C ft_printf/ clean

fclean:		clean
			@$(MAKE) -C libft/ fclean
			@$(MAKE) -C ft_printf/ fclean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all	clean fclean re libft ft_printf bonus
