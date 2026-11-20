NAME		=	push_swap

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

INCLUDES	=	-I. -I$(LIBFT_DIR)

SRCS		=	bench.c \
				dest_loc.c \
				disorder.c \
				dispatch.c \
				errors.c \
				index.c \
				main.c \
				moves.c \
				ops_rev_rotate.c \
				ops_rotate.c \
				ops_swap_push.c \
				optimize.c \
				parse_args.c \
				parse_flags.c \
				primitives.c \
				quick_base.c \
				quick_loc.c \
				record.c \
				sort_complex.c \
				sort_medium.c \
				sort_simple.c \
				sort_small.c \
				stack_query.c \
				stack_utils.c \
				turk_rot.c \
				turk_target.c

OBJS		=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

FORCE:

.PHONY: all clean fclean re FORCE
