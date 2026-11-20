/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 16:27:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 15:40:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft/libft.h"

typedef enum e_ops
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_SIZE
}	t_ops;

typedef enum e_strat
{
	STRAT_ADAPTIVE,
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX
}	t_strat;

typedef enum e_loc
{
	TOP_A,
	BOT_A,
	TOP_B,
	BOT_B
}	t_loc;

typedef struct s_node
{
	struct s_node	*next;
	int				content;
	struct s_node	*previous;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	int		size;
}	t_stack;

typedef struct s_ctx
{
	t_stack	*a;
	t_stack	*b;
	int		ops_count[OP_SIZE];
	t_ops	*buf;
	int		len;
	int		cap;
	int		alloc_failed;
}	t_ctx;

typedef struct s_cfg
{
	t_strat	strat;
	int		bench;
}	t_cfg;

typedef struct s_rot
{
	int	a;
	int	b;
}	t_rot;

void	swap(t_stack *stack);
void	push(t_stack *src, t_stack *dst);
void	rotate(t_stack *stack);
void	rev_rotate(t_stack *stack);

void	sa(t_ctx *ctx);
void	ss(t_ctx *ctx);
void	sb(t_ctx *ctx);
void	pa(t_ctx *ctx);
void	pb(t_ctx *ctx);
void	ra(t_ctx *ctx);
void	rb(t_ctx *ctx);
void	rr(t_ctx *ctx);
void	rra(t_ctx *ctx);
void	rrb(t_ctx *ctx);
void	rrr(t_ctx *ctx);

char	*op_name(t_ops op);
void	record_op(t_ctx *ctx, t_ops op);
void	flush_ops(t_ctx *ctx);

double	disorder(t_stack *a);

int		parse_flags(char **argv, t_cfg *cfg);
int		parse_number(char *str, int *out);
int		parse_args(char **argv, int start, t_stack *a);

t_node	*new_node(int value);
int		add_bottom(t_stack *stack, int value);
int		has_value(t_stack *stack, int value);
void	free_stack(t_stack *stack);

void	free_ctx(t_ctx *ctx);
void	error_exit(t_ctx *ctx);

t_strat	resolve_strat(t_strat strat, double dis);
void	sort_with(t_ctx *ctx, t_strat strat);
void	run_push_swap(t_ctx *ctx, t_cfg *cfg);

int		*stack_to_array(t_stack *a);
void	sort_array(int *arr, int size);
int		normalize(t_stack *a);

int		is_sorted(t_stack *s);
int		find_min_pos(t_stack *s);
int		find_max_pos(t_stack *s);
int		get_max(t_stack *s);

void	bring_to_top_a(t_ctx *ctx, int pos);
void	bring_to_top_b(t_ctx *ctx, int pos);

void	sort_two(t_ctx *ctx);
void	sort_three(t_ctx *ctx);
void	sort_five(t_ctx *ctx);
void	sort_small(t_ctx *ctx);
void	sort_simple(t_ctx *ctx);
int		target_in_b(t_stack *b, int v);
int		target_in_a(t_stack *a, int v);
int		rot_cost(t_rot r);
t_rot	best_rot(int pos_a, int size_a, int pos_b, int size_b);
void	apply_rot(t_ctx *ctx, t_rot r);
int		chunk_size(int n);
void	push_chunks(t_ctx *ctx, int range);
void	push_back_max(t_ctx *ctx);
void	sort_medium(t_ctx *ctx);
void	sort_complex(t_ctx *ctx);

int		local_rank(t_ctx *ctx, t_loc loc);
void	move(t_ctx *ctx, t_loc src, t_loc dst);
t_loc	dest_high(t_loc loc);
t_loc	dest_mid(t_loc loc);
t_loc	dest_low(t_loc loc);
t_loc	normalize_loc(t_ctx *ctx, t_loc loc, int k);
void	quick_base(t_ctx *ctx, t_loc loc, int k);

char	*strat_name(t_strat strat);
char	*strat_complexity(t_strat strat);
int		total_ops(t_ctx *ctx);
void	put_percent_fd(double dis, int fd);
void	print_bench(t_ctx *ctx, t_strat asked, t_strat used, double dis);

#endif
