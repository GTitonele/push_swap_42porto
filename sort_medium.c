/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilherme <guilherme@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/19 19:25:01 by guilherme        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	chunk_size(int n)
{
	int	r;

	r = 1;
	while ((r + 1) * (r + 1) <= n)
		r++;
	return (r * 2);
}

void	push_chunks(t_ctx *ctx, int range)
{
	int	i;
	int	top;

	i = 0;
	while (ctx->a->size > 0)
	{
		top = ctx->a->top->content;
		if (top <= i)
		{
			pb(ctx);
			rb(ctx);
			i++;
		}
		else if (top <= i + range)
		{
			pb(ctx);
			i++;
		}
		else
			ra(ctx);
	}
}

void	push_back_max(t_ctx *ctx)
{
	while (ctx->b->size > 0)
	{
		bring_to_top_b(ctx, find_max_pos(ctx->b));
		pa(ctx);
	}
}

void	sort_medium(t_ctx *ctx)
{
	push_chunks(ctx, chunk_size(ctx->a->size));
	push_back_max(ctx);
}
