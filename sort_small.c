/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaccell <gbaccell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/18 14:42:58 by gbaccell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_ctx *ctx)
{
	if (ctx->a->top->content > ctx->a->top->next->content)
		sa(ctx);
}

void	sort_three(t_ctx *ctx)
{
	int	max;

	max = find_max_pos(ctx->a);
	if (max == 0)
		ra(ctx);
	else if (max == 1)
		rra(ctx);
	if (ctx->a->top->content > ctx->a->top->next->content)
		sa(ctx);
}

void	sort_five(t_ctx *ctx)
{
	while (ctx->a->size > 3)
	{
		bring_to_top_a(ctx, find_min_pos(ctx->a));
		pb(ctx);
	}
	sort_three(ctx);
	while (ctx->b->size > 0)
		pa(ctx);
}

void	sort_small(t_ctx *ctx)
{
	if (ctx->a->size == 2)
		sort_two(ctx);
	else if (ctx->a->size == 3)
		sort_three(ctx);
	else
		sort_five(ctx);
}
