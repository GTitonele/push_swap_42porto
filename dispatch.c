/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 15:40:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_strat	resolve_strat(t_strat strat, double dis)
{
	if (strat != STRAT_ADAPTIVE)
		return (strat);
	if (dis < 0.2)
		return (STRAT_SIMPLE);
	if (dis < 0.5)
		return (STRAT_MEDIUM);
	return (STRAT_COMPLEX);
}

void	sort_with(t_ctx *ctx, t_strat strat)
{
	if (ctx->a->size <= 5)
		sort_small(ctx);
	else if (strat == STRAT_SIMPLE)
		sort_simple(ctx);
	else if (strat == STRAT_MEDIUM)
		sort_medium(ctx);
	else
		sort_complex(ctx);
}

void	run_push_swap(t_ctx *ctx, t_cfg *cfg)
{
	double	dis;
	t_strat	used;

	dis = disorder(ctx->a);
	used = resolve_strat(cfg->strat, dis);
	if (!is_sorted(ctx->a))
	{
		if (!normalize(ctx->a))
			error_exit(ctx);
		sort_with(ctx, used);
		if (ctx->alloc_failed)
			error_exit(ctx);
		flush_ops(ctx);
	}
	if (cfg->bench)
		print_bench(ctx, cfg->strat, used, dis);
}
