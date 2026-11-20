/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 15:40:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 15:40:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_rot	cheapest(t_ctx *ctx)
{
	t_node	*node;
	t_rot	best;
	t_rot	cur;
	int		i;

	node = ctx->a->top;
	best = best_rot(0, ctx->a->size,
			target_in_b(ctx->b, node->content), ctx->b->size);
	node = node->next;
	i = 1;
	while (i < ctx->a->size)
	{
		cur = best_rot(i, ctx->a->size,
				target_in_b(ctx->b, node->content), ctx->b->size);
		if (rot_cost(cur) < rot_cost(best))
			best = cur;
		node = node->next;
		i++;
	}
	return (best);
}

static void	push_back(t_ctx *ctx)
{
	while (ctx->b->size > 0)
	{
		bring_to_top_a(ctx, target_in_a(ctx->a, ctx->b->top->content));
		pa(ctx);
	}
}

void	sort_simple(t_ctx *ctx)
{
	if (ctx->a->size <= 5)
	{
		sort_small(ctx);
		return ;
	}
	while (ctx->a->size > 3 && ctx->b->size < 2)
		pb(ctx);
	while (ctx->a->size > 3)
	{
		apply_rot(ctx, cheapest(ctx));
		pb(ctx);
	}
	sort_three(ctx);
	push_back(ctx);
	bring_to_top_a(ctx, find_min_pos(ctx->a));
}
