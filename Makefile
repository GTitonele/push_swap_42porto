# ================================ PROGRAMA ==================================
NAME		=	push_swap

# =============================== COMPILADOR =================================
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

# ================================== LIBFT ===================================
LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

# ================================ INCLUDES ==================================
INCLUDES	=	-I. -I$(LIBFT_DIR)

# ================================ FONTES ====================================
SRCS		=	disorder.c \
				dispatch.c \
				errors.c \
				main.c \
				ops_rev_rotate.c \
				ops_rotate.c \
				ops_swap_push.c \
				parse_args.c \
				parse_flags.c \
				primitives.c \
				record.c \
				stack_utils.c \
				bench.c \
				index.c \
				moves.c \
				sort_complex.c \
				sort_medium.c \
				sort_simple.c \
				sort_small.c \
				stack_query.c

# checker_bonus.c fica FORA daqui: entra so na futura regra 'bonus'

# ================================ OBJETOS ===================================
OBJS		=	$(SRCS:.c=.o)

# ================================= REGRAS ===================================

# Regra padrao: compila o push_swap
all: $(NAME)

# Linka os objetos com a libft para gerar o executavel
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

# Compila a libft usando o Makefile dela (o FORCE faz o make da libft
# sempre rodar; ela mesma decide se precisa recompilar algo)
$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

# Compila cada .c em .o (recompila se o push_swap.h mudar)
%.o: %.c push_swap.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Remove os objetos (.o) do projeto e da libft
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Remove os objetos e os executaveis/bibliotecas
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Recompila tudo do zero
re: fclean all

# Alvo vazio usado para forcar a execucao da regra da libft
FORCE:

.PHONY: all clean fclean re FORCE