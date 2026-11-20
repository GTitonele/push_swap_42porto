/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 10:30:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 10:30:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_top_three(t_ctx *ctx)
{
	if (ctx->a->top->content > ctx->a->top->next->content)
		sa(ctx);
	if (ctx->a->top->next->content > ctx->a->top->next->next->content)
	{
		pb(ctx);
		sa(ctx);
		pa(ctx);
	}
	if (ctx->a->top->content > ctx->a->top->next->content)
		sa(ctx);
}

void	quick_base(t_ctx *ctx, t_loc loc, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		move(ctx, loc, TOP_A);
		i++;
	}
	if (k == 2 && ctx->a->top->content > ctx->a->top->next->content)
		sa(ctx);
	else if (k == 3 && ctx->a->size == 3)
		sort_three(ctx);
	else if (k == 3)
		sort_top_three(ctx);
}
