/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 10:30:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	partition(t_ctx *ctx, t_loc loc, int lo, int k)
{
	int	p1;
	int	p2;
	int	r;
	int	i;

	p1 = lo + k / 3;
	p2 = lo + 2 * k / 3;
	i = 0;
	while (i < k)
	{
		r = local_rank(ctx, loc);
		if (r >= p2)
			move(ctx, loc, dest_high(loc));
		else if (r >= p1)
			move(ctx, loc, dest_mid(loc));
		else
			move(ctx, loc, dest_low(loc));
		i++;
	}
}

static void	quick_rec(t_ctx *ctx, t_loc loc, int lo, int k)
{
	int	p1;
	int	p2;

	if (k <= 0)
		return ;
	loc = normalize_loc(ctx, loc, k);
	if (k <= 3)
	{
		quick_base(ctx, loc, k);
		return ;
	}
	partition(ctx, loc, lo, k);
	p1 = lo + k / 3;
	p2 = lo + 2 * k / 3;
	quick_rec(ctx, dest_high(loc), p2, lo + k - p2);
	quick_rec(ctx, dest_mid(loc), p1, p2 - p1);
	quick_rec(ctx, dest_low(loc), lo, p1 - lo);
}

void	sort_complex(t_ctx *ctx)
{
	quick_rec(ctx, TOP_A, 0, ctx->a->size);
}
